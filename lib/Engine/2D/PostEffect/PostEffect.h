#pragma once
#include"ErrorException.h"
#include"Transform.h"
#include"Material.h"

class PostEffect
{
private:

	HRESULT result;
	char PADDING[4];
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> cmdList = nullptr;

	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer;

	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer;

	//プロジェクション行列
	AliceMathF::Matrix4 matProjection;

	Material* postEffectMaterial;


	Microsoft::WRL::ComPtr<ID3D12Resource> depthBuff;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapRTV;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	static const float clearColor[4];

	TextureData windowTex;

	std::unique_ptr<ConstantBuffer> lutSizeBuff;

	struct lutSize
	{
		float width;
		float height;
		float lutRed;
		float lutGreen;
		float lutBlue;
		float lutMul;
	};

	float width = 0.0f;
	float height = 0.0f;

	TextureData lutTexture;

	lutSize size = {};

public:
	~PostEffect() = default;
	PostEffect() = default;

	void PostInitialize();

	void PostDraw();

	void PreDrawScen();

	void PostDrawScen();

	void SetLutTexture(TextureData& texture);

private:
	
	void CreateWindowTex();
	
	void CreateRenderTarget();

	void CreateDepthStencilView();

	//コピーコンストラクタ・代入演算子削除
	PostEffect& operator=(const PostEffect&) = delete;
	PostEffect(const PostEffect&) = delete;

};


