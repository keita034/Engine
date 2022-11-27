#pragma once
#include"ErrorException.h"
#include"Model.h"

class PrimitiveModel :public Model
{
private:
	//キューブのインデックス数と頂点数
	const UINT cubeMaxIndex = 36;
	const UINT cubeMaxVert = 24;

	//円錐のインデックス数と頂点数
	const UINT coneMaxIndex = 191;
	const UINT coneMaxVert = 66;

	//シリンダーのインデックス数と頂点数
	const UINT cylinderMaxIndex = 384;
	const UINT cylinderMaxVert = 132;

	//球のインデックス数と頂点数
	const UINT sphereMaxIndex = 3072;
	const UINT sphereMaxVert = 560;

public:

	PrimitiveModel() = default;
	~PrimitiveModel() = default;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Transform* transform, Material* material = nullptr)override;

	//初期化
	void Initialize(ModelShape shape)override;

private:

	void CubeCreate();

	void ConeCreate();

	void CylinderCreate();

	void SphereCreate();


	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create(bool smoothing = false)override;

	virtual void Create(const char* filePath, bool smoothing = false);

	virtual void Initialize(const char* filePath, bool smoothing);

	PrimitiveModel& operator=(const PrimitiveModel&) = delete;
	PrimitiveModel(const PrimitiveModel&) = delete;
};
