#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Collision.h"
#include "MeshCollider.h"

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::AddCollider(BaseCollider* collider)
{
	colliders.push_front(collider);
}

void CollisionManager::RemoveCollider(BaseCollider* collider)
{
	colliders.remove(collider);
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	// 全ての組み合わせについて総当りチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			// ともに球
			if (colA->GetShapeType() == CollisionShapeSphere &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				AliceMath::Vector4 inter;
				if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
			else if (colA->GetShapeType() == CollisionShapeMesh &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
				Sphere* sphere = dynamic_cast<Sphere*>(colB);
				AliceMath::Vector4 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
			else if (colA->GetShapeType() == CollisionShapeSphere &&
				colB->GetShapeType() == CollisionShapeMesh)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colB);
				Sphere* sphere = dynamic_cast<Sphere*>(colA);
				AliceMath::Vector4 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
		}
	}
}

bool CollisionManager::Raycast(Ray& ray, RaycastHit* hitInfo, float maxDistance)
{
	return Raycast(ray, 0xffff, hitInfo, maxDistance);
}

bool CollisionManager::Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitInfo, float maxDistance)
{
	bool result = false;
	std::forward_list<BaseCollider*>::iterator it;
	std::forward_list<BaseCollider*>::iterator it_hit;
	float distance = maxDistance;
	AliceMath::Vector4 inter;

	// 全てのコライダーと総当りチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;

		// 属性が合わなければスキップ
		if (!(colA->attribute & attribute))
		{
			continue;
		}

		if (colA->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);

			float tempDistance;
			AliceMath::Vector4 tempInter;

			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter))
			{
				continue;
			}

			if (tempDistance >= distance)
			{
				continue;
			}

			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
		else if (colA->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance;
			AliceMath::Vector4 tempInter;
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tempInter))
			{
				continue;
			}

			if (tempDistance >= distance)
			{
				continue;
			}

			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
		}
	}

	if (result && hitInfo)
	{
		hitInfo->distance = distance;
		hitInfo->inter = inter;
		hitInfo->collider = *it_hit;
		hitInfo->object = hitInfo->collider->model;
	}

	return result;
}

void CollisionManager::QuerySphere(Sphere& sphere, QueryCallback* callback, uint16_t attribute)
{
	assert(callback);

	std::forward_list<BaseCollider*>::iterator it;

	// 全てのコライダーと総当りチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		// 属性が合わなければスキップ
		if (!(col->attribute & attribute))
		{
			continue;
		}

		// 球
		if (col->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			AliceMath::Vector4 tempInter;
			AliceMath::Vector4 tempReject;
			if (!Collision::CheckSphere2Sphere(sphere, *sphereB, &tempInter, &tempReject)) continue;

			// 交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->GetModel();
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}
		// メッシュ
		else if (col->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(col);

			AliceMath::Vector4 tempInter;
			AliceMath::Vector4 tempReject;
			if (!meshCollider->CheckCollisionSphere(sphere, &tempInter, &tempReject))
			{
				continue;
			}

			// 交差情報をセット
			QueryHit info;
			info.collider = col;
			info.object = col->model;
			info.inter = tempInter;
			info.reject = tempReject;

			// クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				// 戻り値がfalseの場合、継続せず終了
				return;
			}
		}
	}
}