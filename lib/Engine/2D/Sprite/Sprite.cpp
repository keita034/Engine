#include "Sprite.h"
#include "DirectX12Core.h"
#include"Sprite2D.h"
#include"Sprite3D.h"

void Sprite::SpriteInitialize()
{
	device = DirectX12Core::GetDeviceSta();
	cmdList = DirectX12Core::GetCommandListSta();
}

void Sprite::SpriteDraw(Transform& transform, Material* material)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(material->pipelineState->GetPipelineState());
	cmdList->SetGraphicsRootSignature(material->rootSignature->GetRootSignature());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, transform.GetconstBuff()->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, texture.srvHeap.GetAddressOf());

	//// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, texture.gpuHandle);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Sprite::CreatVertexIndexBuffer()
{
	//頂点バッファの生成
	vertexBuffer = std::make_unique<VertexBuffer>();
	vertexBuffer->Create(4, sizeof(PosUvColor));

	//インデックスバッファの生成
	indexBuffer = std::make_unique<IndexBuffer>();
	indexBuffer->Create(6);
}

void Sprite::SetAnchorPoint(const AliceMathF::Vector2& point)
{
	anchorPoint = point;
}

void Sprite::SetFlipFlag(bool isFlipX, bool isFlipY)
{
	flipX = isFlipX;
	flipY = isFlipY;
}

void Sprite::SetColor(const AliceMathF::Vector4& color)
{
	texture.color = color;
}

void Sprite::SetTextureTrimmingRange(const AliceMathF::Vector2& leftTop, const AliceMathF::Vector2& rightDown)
{
	trimmingRange = { leftTop.x,leftTop.y,rightDown.x,rightDown.y };
}

void Sprite::SetTex(const TextureData& textureData)
{
	texture = textureData;
	trimmingRange.z = static_cast<float>(texture.width);
	trimmingRange.w = static_cast<float>(texture.height);
}

Sprite2D* Sprite::Create2DSprite(const TextureData& textureData)
{
	Sprite2D* s2D = new Sprite2D;
	s2D->Initialize(textureData);
	return s2D;
}

Sprite3D* Sprite::Create3DSprite(const TextureData& textureData)
{
	Sprite3D* s3D = new Sprite3D;
	s3D->Initialize(textureData);
	return s3D;
}
