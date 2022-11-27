#pragma once
#include"BaseCollider.h"
#include"AliceMath.h"
#include"CollisionInfo.h"
#include"CollisionPrimitive.h"
#include"ModelInterface.h"

class SphereCollider : public BaseCollider,public Sphere
{
private:
	// オブジェクト中心からのオフセット
	AliceMath::Vector3 offset;
	// 半径
	float radius;

public:
	SphereCollider(AliceMath::Vector3 offset = { 0,0,0 }, float radius = 1.0f);

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	void SetRadius(float radius_);

	virtual void SetModel(ModelInterface* model_)override;

	virtual ModelInterface* GetModel()override;

	virtual CollisionShapeType GetShapeType()override;

	virtual void OnCollision(const CollisionInfo& info)override;

	virtual void SetAttribute(uint16_t attribute_)override;

	virtual void AddAttribute(uint16_t attribute_)override;

	virtual void RemoveAttribute(uint16_t attribute_)override;

	AliceMath::Vector3& GetOffset();

	void SetOffset(AliceMath::Vector3& offset_);

	float GetRadius();
};

