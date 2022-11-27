#include "SphereCollider.h"

SphereCollider::SphereCollider(AliceMath::Vector3 offset, float radius) :
	offset(offset),
	radius(radius)
{
	// 球形状をセット
	shapeType = CollisionShapeSphere;
}

void SphereCollider::Update()
{
	// ワールド行列から座標を抽出
	const AliceMath::Matrix4 matWorld = model->GetMatWorld();

	// 球のメンバ変数を更新
	center =
	{
		matWorld.m[3][0] + offset.x,
		matWorld.m[3][1] + offset.y,
		matWorld.m[3][2] + offset.z
	};
	radius = radius;
}

void SphereCollider::SetRadius(float radius_)
{
	radius = radius_;
}

void SphereCollider::SetModel(ModelInterface* model_)
{
	model = model_;
}

ModelInterface* SphereCollider::GetModel()
{
	return model;
}

CollisionShapeType SphereCollider::GetShapeType()
{
	return shapeType;
}

void SphereCollider::OnCollision(const CollisionInfo& info)
{
	model->OnCollision(info);
}

void SphereCollider::SetAttribute(uint16_t attribute_)
{
	attribute = attribute_;
}

void SphereCollider::AddAttribute(uint16_t attribute_)
{
	attribute |= attribute_;
}

void SphereCollider::RemoveAttribute(uint16_t attribute_)
{
	attribute &= !attribute_;
}

AliceMath::Vector3& SphereCollider::GetOffset()
{
	return offset;
}

void SphereCollider::SetOffset(AliceMath::Vector3& offset_)
{
	offset = offset_;
}

float SphereCollider::GetRadius()
{
	return radius;
}
