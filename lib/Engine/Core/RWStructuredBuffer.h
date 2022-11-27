#pragma once
#include"ErrorException.h"

/// <summary>
/// 書き込みと読み込み用構造化バッファ
/// </summary>
class RWStructuredBuffer
{

private:

	// バッファ生成に成功したか
	bool isValid = false;
	char PADING[7] = {};

	// バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> buffer;

	void* BufferMappedPtr = nullptr;

	//個数
	size_t bufferLength;

	//データ一つ分のサイズ
	size_t bufferSingleSize;

	D3D12_GPU_DESCRIPTOR_HANDLE structuredBufferHandle;
public:
	
	/// <summary>
	/// シェーダーリソースビューを生成
	/// </summary>
	/// <param name="length">要素数</param>
	/// <param name="singleSize">要素1つ分のデータサイズ</param>
	/// <param name="data">データ</param>
	void CreateSRV(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// アンオーダーアクセスビューを生成
	/// </summary>
	/// <param name="length">個数</param>
	/// <param name="singleSize">要素1つ分のデータサイズ</param>
	/// <param name="data">データ</param>
	void CreateUAV(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// バッファ生成に成功したかを返す
	/// </summary>
	bool IsValid();

	/// <summary>
	/// バッファのGPU上のアドレスを返す
	/// </summary>
	/// <returns>バッファのGPU上のアドレス</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetAddress() const;

	/// <summary>
	/// 定数バッファビューを返す
	/// </summary>
	/// <returns>定数バッファビュー</returns>
	D3D12_SHADER_RESOURCE_VIEW_DESC GetViewDesc();

	/// <summary>
	/// バッファを取得
	/// </summary>
	ID3D12Resource* GetResource();

	/// <summary>
	/// 定数バッファにマッピングされたポインタを返す
	/// </summary>
	/// <returns>定数バッファにマッピングされたポインタ</returns>
	void* GetPtr() const;

	/// <summary>
	/// データを更新
	/// </summary>
	/// <param name="data"></param>
	void Update(void* data);

	~RWStructuredBuffer() = default;
	RWStructuredBuffer() = default;

private:

	RWStructuredBuffer(const RWStructuredBuffer&) = delete;
	void operator = (const RWStructuredBuffer&) = delete;

};