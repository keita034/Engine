#pragma once
#include "BaseCollider.h"

class ModelInterface;

/// <summary>
/// レイキャストによる情報を得る為の構造体
/// </summary>
struct RaycastHit
{
	// 衝突相手のオブジェクト
	ModelInterface* object = nullptr;
	// 衝突相手のコライダー
	BaseCollider* collider = nullptr;
	// 衝突点
	AliceMath::Vector4 inter;
	// 衝突点までの距離
	float distance = 0.0f;
	char PADDING[4]{};
};