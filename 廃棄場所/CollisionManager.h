#pragma once
#include"ErrorException.h"
#include"RaycastHit.h"
#include"CollisionPrimitive.h"
#include"QueryCallback.h"

class BaseCollider;

class CollisionManager
{
private:
	//コライダーのリスト
	std::forward_list<BaseCollider*> colliders;

public:
	static CollisionManager* GetInstance();

	/// <summary>
	/// コライダーの追加
	/// </summary>
	/// <param name="collider">コライダー</param>
	void AddCollider(BaseCollider* collider);

	/// <summary>
	/// コライダーの削除
	/// </summary>
	/// <param name="collider">コライダー</param>
	void RemoveCollider(BaseCollider* collider);

	/// <summary>
	/// 全ての衝突チェック
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// レイキャスト
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="hitinfo">衝突情報</param>
	/// <param name="maxDistance">最大距離</param>
	/// <returns>レイがコライダーに当たっているか</returns>
	bool Raycast( Ray& ray, RaycastHit* hitinfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// レイキャスト
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="attribute">対象の衝突属性</param>
	/// <param name="hitinfo">衝突情報</param>
	/// <param name="maxDistance">最大距離</param>
	/// <returns>レイがコライダーに当たっているか</returns>
	bool Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitinfo = nullptr, float maxDistance = D3D12_FLOAT32_MAX);

	/// <summary>
	/// 球による衝突全検索
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="callback">衝突時コールバック</param>
	/// <param name="attribute">対象の衝突属性</param>
	void QuerySphere(Sphere& sphere,QueryCallback* callback, uint16_t attribute = static_cast<uint16_t>(0xffffffff));

private:
	CollisionManager() = default;
	CollisionManager(const CollisionManager&) = default;
	~CollisionManager() = default;
	CollisionManager& operator=(const CollisionManager&) = default;

	//球と球
	void Sphere2Sphere(BaseCollider* SphereA, BaseCollider* SphereB);


};

