#pragma once
#include "BaseCollider.h"
#include"CollisionPrimitive.h"
#include"AliceMath.h"
#include"ModelInterface.h"

/// <summary>
/// メッシュ衝突判定オブジェクト
/// </summary>
class MeshCollider : public BaseCollider
{
private:
	std::vector<Triangle>triangles;
	//ワールド行列
	AliceMath::Matrix4 invMatWorld;
public:
	MeshCollider();

	/// <summary>
	/// 三角形の配列を構築する
	/// </summary>
	void ConstructTriangles(ModelInterface* model_);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update()override;

	virtual void SetModel(ModelInterface* model)override;

	virtual ModelInterface* GetModel()override;

	virtual CollisionShapeType GetShapeType()override;

	virtual void OnCollision(const CollisionInfo& info)override;

	/// <summary>
	/// 球との当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか</returns>
	bool CheckCollisionSphere(Sphere& sphere, AliceMath::Vector4* inter = nullptr, AliceMath::Vector4* reject = nullptr);

	/// <summary>
	/// レイとの当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="distance">距離(出力用)</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか</returns>
	bool CheckCollisionRay(Ray& ray, float* distance = nullptr, AliceMath::Vector4* inter = nullptr);

	virtual void SetAttribute(uint16_t attribute_)override;

	virtual void AddAttribute(uint16_t attribute_)override;

	virtual void RemoveAttribute(uint16_t attribute_)override;

};

