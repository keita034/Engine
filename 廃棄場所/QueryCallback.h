#pragma once
#include"AliceMath.h"

class ModelInterface;
class BaseCollider;

/// <summary>
/// クエリーによる情報を得るための構造体
/// </summary>
struct QueryHit
{
	//衝突相手のオブジェクト
	ModelInterface* model = nullptr;
	//衝突相手のコライダー
	BaseCollider* collider = nullptr;
	//諸突点
	AliceMath::Vector3 inter;
	//排斥ベクトル
	AliceMath::Vector3 reject;
};

/// <summary>
/// クエリーで交差を検出した時の動作を既定するクラス
/// </summary>
class QueryCallback
{
public:
	QueryCallback() = default;
	virtual ~QueryCallback() = default;

	/// <summary>
	/// 交差時コールバック
	/// </summary>
	/// <param name="info">交差情報</param>
	/// <returns>クエリーを続けるならtrue,打ち切るならfalseを返す</returns>
	virtual bool OnQueryHit(QueryHit& info) = 0;

};