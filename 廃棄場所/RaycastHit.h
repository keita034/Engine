#pragma once
#include"BaseCollider.h"
#include"ModelInterface.h"
#include"AliceMath.h"

struct RaycastHit
{
	//衝突相手のオブジェクト
	ModelInterface* model = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//衝突点
	AliceMath::Vector3 inter;
	//衝突点までの距離
	float distance = 0.0f;

};
