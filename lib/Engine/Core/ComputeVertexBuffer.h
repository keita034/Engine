#pragma once
#include"ErrorException.h"

/// <summary>
/// コンピュートシェーダー用頂点バッファ
/// </summary>
class ComputeVertexBuffer
{
private:
	// バッファ
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer = nullptr;

	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};

	D3D12_GPU_DESCRIPTOR_HANDLE handl = {};

	void* bufferMappedPtr = nullptr;

	// バッファの生成に成功したか
	bool isValid = false;
	char PADING[7];
public:

	/// <summary>
	/// バッファを生成
	/// </summary>
	/// <param name="length">要素数</param>
	/// <param name="singleSize">単体のサイズ</param>
	/// <param name="data">配列のポインタ</param>
	void Create(size_t length, size_t singleSize, const void* data = nullptr);

	/// <summary>
	/// 頂点バッファビューを取得
	/// </summary>
	/// <returns>頂点バッファビュー</returns>
	D3D12_VERTEX_BUFFER_VIEW GetView() const;

	ID3D12Resource* GetResource();

	/// <summary>
	/// バッファの生成に成功したかを取得
	/// </summary>
	/// <returns>成功したか</returns>
	bool IsValid();

	/// <summary>
	/// バッファのGPU上のアドレスを返す
	/// </summary>
	/// <returns>バッファのGPU上のアドレス</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetAddress() const;

	/// <summary>
	/// バッファの状態を変える
	/// </summary>
	/// <param name="beforeState">今の状態</param>
	/// <param name="afterState">変えたい状態</param>
	void Transition(D3D12_RESOURCE_STATES beforeState, D3D12_RESOURCE_STATES afterState);

	/// <summary>
	/// データ更新
	/// </summary>
	/// <param name="data">データ</param>
	void Update(void* data);

	~ComputeVertexBuffer() = default;
	ComputeVertexBuffer() = default;

private:

	ComputeVertexBuffer(const ComputeVertexBuffer&) = delete;

	void operator = (const ComputeVertexBuffer&) = delete;
};

