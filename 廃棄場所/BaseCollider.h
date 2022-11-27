#pragma once

#include "CollisionShapeType.h"
#include"CollisionInfo.h"
class ModelInterface;

/// <summary>
/// コライダー基底クラス
/// </summary>
class BaseCollider
{
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	virtual void SetModel(ModelInterface* model) = 0;

	virtual ModelInterface* GetModel() = 0;

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	virtual CollisionShapeType GetShapeType() = 0;

	virtual void OnCollision(const CollisionInfo& info) = 0;

	friend class CollisionManager;

	virtual void SetAttribute(uint16_t attribute_) = 0;
	
	virtual void AddAttribute(uint16_t attribute_) = 0;

	virtual void RemoveAttribute(uint16_t attribute_) = 0;

protected:
	ModelInterface* model = nullptr;

	//形状タイプ
	CollisionShapeType shapeType = ShapeUnknown;

	//当たり判定属性
	uint16_t attribute = static_cast<uint16_t>(0b111111111111111111);

	char PADDING[2]{};
};