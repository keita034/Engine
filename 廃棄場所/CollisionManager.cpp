#include "CollisionManager.h"
#include"BaseCollider.h"
#include"Collision.h"
#include"MeshCollider.h"

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

	//全ての組み合わせについて総当たりチェック
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		itB++;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
			BaseCollider* colB = *itB;

			//ともに球
			if (colA->GetShapeType() == CollisionShapeSphere &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				Sphere2Sphere(colA, colB);
			}
			else if (colA->GetShapeType() == CollisionShapeMesh &&
				colB->GetShapeType() == CollisionShapeSphere)
			{
				MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);
				Sphere* sphere = dynamic_cast<Sphere*>(colB);
				AliceMath::Vector3 inter;
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
				AliceMath::Vector3 inter;
				if (meshCollider->CheckCollisionSphere(*sphere, &inter))
				{
					colA->OnCollision(CollisionInfo(colB->GetModel(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetModel(), colA, inter));
				}
			}
		}
	}
}

bool CollisionManager::Raycast(Ray& ray, RaycastHit* hitinfo, float maxDistance)
{
	//全属性有効にして属性版を実行
	return Raycast(ray, 0xffff, hitinfo, maxDistance);
}

bool CollisionManager::Raycast(Ray& ray, uint16_t attribute, RaycastHit* hitinfo, float maxDistance)
{
	bool result = false;
	//捜査用のイテレータ
	std::forward_list<BaseCollider*>::iterator it;
	//今まで一番近いコライダーを記録するイテレータ
	std::forward_list<BaseCollider*>::iterator it_hit;
	//今まで一番近いコライダーの距離
	float distance = maxDistance;
	//最も近いコライダーの交点
	AliceMath::Vector3 inter;
	//全てのコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;

		//属性が合わなければスキップ
		if (!(colA->attribute & attribute))
		{
			continue;
		}

		//球の場合
		if (colA->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			AliceMath::Vector3 templnter;

			//当たらなければ除外
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &templnter))
			{
				continue;
			}

			//距離が最小でなければ除外
			if (tempDistance >= distance)
			{
				continue;
			}

			//今までで最も近いので記録を取る
			result = true;
			distance = tempDistance;
			inter = templnter;
			it_hit = it;
		}
		else if (colA->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshCollider = dynamic_cast<MeshCollider*>(colA);

			float tempDistance = 0.0;
			AliceMath::Vector3 tmplnter;
			if (!meshCollider->CheckCollisionRay(ray, &tempDistance, &tmplnter))
			{
				continue;
			}

			//距離が最小でなければ除外
			if (tempDistance >= distance)
			{
				continue;
			}

			result = true;
			distance = tempDistance;
			inter = tmplnter;
			it_hit = it;
		}
	}

	if (result && hitinfo)
	{
		hitinfo->distance = distance;
		hitinfo->inter = inter;
		hitinfo->collider = *it_hit;
		hitinfo->model = hitinfo->collider->GetModel();
	}

	return result;
}

void CollisionManager::QuerySphere(Sphere& sphere, QueryCallback* callback, uint16_t attribute)
{
	assert(callback);
	std::forward_list<BaseCollider*>::iterator it;

	//全てののコライダーと総当たりチェック
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* col = *it;

		//属性が合わなければスキップ
		if (!(col->attribute & attribute))
		{
			continue;
		}

		if (col->GetShapeType() == CollisionShapeSphere)
		{
			Sphere* sphereB = dynamic_cast<Sphere*>(col);

			AliceMath::Vector3 templnter;
			AliceMath::Vector3 tempReject;
			if (!Collision::CheakSphere2Sphere(sphere, *sphereB, &templnter, &tempReject))
			{
				continue;
			}

			//交差情報をセット
			QueryHit info;
			info.collider = col;
			info.model = col->GetModel();
			info.inter = templnter;
			info.reject = tempReject;

			//クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				//戻り値がfalseの場合、継続せずに終了
				return;
			}
		}
		else if (col->GetShapeType() == CollisionShapeMesh)
		{
			MeshCollider* meshcollider = dynamic_cast<MeshCollider*>(col);

			AliceMath::Vector3 templnter;
			AliceMath::Vector3 tempReject;
			if (!meshcollider->CheckCollisionSphere(sphere, &templnter, &tempReject))
			{
				continue;
			}

			//交差情報をセット
			QueryHit info;
			info.collider = col;
			info.model = col->GetModel();
			info.inter = templnter;
			info.reject = tempReject;

			//クエリーコールバック呼び出し
			if (!callback->OnQueryHit(info))
			{
				//戻り値がfalseの場合、継続せずに終了
				return;
			}

		}

	}
}

void CollisionManager::Sphere2Sphere(BaseCollider* SphereA, BaseCollider* SphereB)
{
	Sphere* sphereA = dynamic_cast<Sphere*>(SphereA);
	Sphere* sphereB = dynamic_cast<Sphere*>(SphereB);
	AliceMath::Vector3 inter;

	if (Collision::CheakSphere2Sphere(*sphereA, *sphereB, &inter))
	{
		SphereA->OnCollision(CollisionInfo(SphereB->GetModel(), SphereB, inter));
		SphereB->OnCollision(CollisionInfo(SphereA->GetModel(), SphereA, inter));
	}

}
