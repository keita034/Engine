#pragma once
#include"AliceMath.h"

class ModelInterface;
class BaseCollider;

// <summary>
/// 衝突情報
/// </summary>
struct CollisionInfo
{
	CollisionInfo(ModelInterface* object, BaseCollider* collider, const AliceMath::Vector4& inter);

	// 衝突相手のオブジェクト
	ModelInterface* object = nullptr;
	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	AliceMath::Vector4 inter;
};