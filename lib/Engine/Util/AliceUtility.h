#pragma once
#include"ErrorException.h"
#include"AliceMathUtility.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"

struct TextureData
{
	//テクスチャバッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> texBuff;

	//デスクプリタヒープ
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap> srvHeap;

	//GPUデスクプリタハンドル
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//横幅
	size_t width = 0;
	//縦幅
	size_t height = 0;

	//カラー
	AliceMathF::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };

	std::string path;
};

//座標変換行列
struct ConstBufferDataTransform
{
	AliceMathF::Matrix4 mat;//3D変換行列
};


struct PosColor
{
	AliceMathF::Vector3 pos;//座標
	AliceMathF::Vector4 color;//カラー
};

struct PosNormalUv
{
	AliceMathF::Vector3 pos;//座標
	AliceMathF::Vector3 normal;//法線ベクトル
	AliceMathF::Vector2 uv;//uv座標
};

//座標・UV・カラー
struct PosUvColor
{
	AliceMathF::Vector3 pos;//座標
	AliceMathF::Vector2 uv;//uv座標
	AliceMathF::Vector4 color;//カラー
};

typedef struct
{
	//パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	//デスクプリタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap;
	//デスクプリタレンジ
	D3D12_DESCRIPTOR_RANGE descriptorRange;
	//スプライト数
	UINT nextIndex;
}ModelShareVaria;

//パイプライン・ルートシグネチャセット
struct PipelineSet
{
	//パイプラインステート
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	//ルートシグネチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
};

struct worldViewpojCamera
{
	//ワールド行列
	AliceMathF::Matrix4 world;
	//ワールド座標
	AliceMathF::Matrix4 matWorld;
	//カメラ座標(ワールド座標)
	AliceMathF::Vector3 cameraPos;
};

//マテリアルよう定数バッファ構造体
struct ConstBuffDataMaterial
{
	//アンビエント係数
	AliceMathF::Vector3 ambient;
	//パディング
	float pad1;
	//ディフューズ係数
	AliceMathF::Vector3 diffuse;
	//パディング
	float pad2;
	//スペキュラー係数
	AliceMathF::Vector3 specular;
	//アルファ
	float alpha;
};

//マテリアル
struct ModelMaterial
{
	//マテリアル名
	std::string name;
	//アンビエント影響度
	AliceMathF::Vector3 ambient = { 0.06f, 0.06f, 0.06f };
	//ディフューズ影響度
	AliceMathF::Vector3 diffuse = { 0.0f,0.0f,0.0f };
	//スペキュラー影響度
	AliceMathF::Vector3 specular = { 0.0f,0.0f,0.0f };

	AliceMathF::Vector3 emission = { 0.0f,0.0f,0.0f };

	float shininess = 1.0f;
	//アルファ
	float alpha = 1.0f;
	//テクスチャファイル名
	std::string textureFiename;

	ConstBuffDataMaterial GetConstBuffMaterial();
};

//バッファ関連
struct Buff
{
	//頂点バッファ
	std::unique_ptr<VertexBuffer> vertexBuffer;
	//頂点マップ
	PosColor* vertMap;
	//インデックスバッファ
	std::unique_ptr<IndexBuffer> indexBuffer;
	//インデックスマップ
	uint32_t* indexMap;

	Buff() = default;
	~Buff() = default;

private:
	//コピーコンストラクタ・代入演算子削除
	Buff& operator=(const Buff&) = delete;
	Buff(const Buff&) = delete;

};

//ブレンドモード
enum class BlendMode
{
	AX_BLENDMODE_NOBLEND,//ノーブレンド（デフォルト）
	AX_BLENDMODE_ALPHA,//αブレンド
	AX_BLENDMODE_ADD,//加算ブレンド
	AX_BLENDMODE_SUB,//減算ブレンド
	AX_BLENDMODE_MULA,//乗算ブレンド
	AX_BLENDMODE_INVSRC,//反転ブレンド

	AX_BLENDMODE_MAX,//ブレンド種類数

	AX_BLENDMODE_CUSTOM = -1,
};