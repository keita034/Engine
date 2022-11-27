#include "MeshCollider.h"
#include"Collision.h"

MeshCollider::MeshCollider()
{
	//メッシュ形状をセット
	shapeType = CollisionShapeMesh;
}

void MeshCollider::CnnstructTriangles(ModelInterface* model_)
{
	//三角形リストをクリア
	triangle.clear();
	//インデックスは、三角形の数×3個あるので
	//そこからメッシュ内の三角形の数を逆算する
	size_t triangleNum = model_->GetIndices().size() / 3;
	triangle.resize(triangleNum);
	for (size_t i = 0; i < triangleNum; i++)
	{
		//今から計算する三角形の参照
		Triangle& tri = triangle[i];
		uint64_t idx0 = model_->GetIndices()[i * 3 + 0];
		uint64_t idx1 = model_->GetIndices()[i * 3 + 1];
		uint64_t idx2 = model_->GetIndices()[i * 3 + 2];
		//三角形の3頂点の座標を代入
		tri.p0 = { model_->GetVertices()[idx0].pos.x,model_->GetVertices()[idx0].pos.y,model_->GetVertices()[idx0].pos.z };
		tri.p1 = { model_->GetVertices()[idx1].pos.x,model_->GetVertices()[idx1].pos.y,model_->GetVertices()[idx1].pos.z };
		tri.p2 = { model_->GetVertices()[idx2].pos.x,model_->GetVertices()[idx2].pos.y,model_->GetVertices()[idx2].pos.z };
		//3頂点から法線を計算
		tri.ComputeNormal();
	}
}

void MeshCollider::Update()
{
	//ワールド行列の逆行列を計算
	invMatWorld = AliceMath::MakeInverse(&GetModel()->GetMatWorld());
}

void MeshCollider::SetModel(ModelInterface* model_)
{
	model = model_;
}

ModelInterface* MeshCollider::GetModel()
{
	return model;
}

CollisionShapeType MeshCollider::GetShapeType()
{
	return shapeType;
}

void MeshCollider::OnCollision(const CollisionInfo& info)
{
	static_cast<void>(info);
}

bool MeshCollider::CheckCollisionSphere(Sphere& sphere, AliceMath::Vector3* inter, AliceMath::Vector3* reject)
{
	Sphere localSphere;
	AliceMath::Vector4 tmp = { sphere.center.x,sphere.center.y,sphere.center.z,1.0f};
	tmp = AliceMath::Vector4Trns(tmp, invMatWorld);
	localSphere.center = { tmp.x,tmp.y,tmp.z };
	AliceMath::Vector4 vec = { invMatWorld.m[0][0],invMatWorld.m[0][1] ,invMatWorld.m[0][2] ,invMatWorld.m[0][3] };
	localSphere.radius *= vec.length();

	//ローカル座標系で交差をチェック
	std::vector<Triangle>::const_iterator it = triangle.cbegin();

	for (; it != triangle.cend(); ++it)
	{
		const Triangle& triangle_ = *it;

		//球と三角形の当たり判定
		if (Collision::CheckSphere2Triangle(localSphere, triangle_, inter, reject))
		{
			if (inter)
			{
				AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();
				//ワールド座標での交点を得る
				tmp = {inter->x,inter->y,inter->z,1.0f };
				tmp = AliceMath::Vector4Trns(tmp, matWorld);
				*inter = { tmp.x,tmp.y,tmp.z };
			}
			if (reject)
			{
				AliceMath::Matrix4 matWorld = GetModel()->GetMatWorld();
				//ワールド座標系での排斥ベクトルに変換
				tmp = { reject->x,reject->y,reject->z,1.0f };
				tmp = AliceMath::Vector4Trns(tmp, matWorld);
				*reject = { tmp.x,tmp.y,tmp.z };
			}

			return true;
		}
	}
	return false;
}

bool MeshCollider::CheckCollisionRay(Ray& ray, float* distance, AliceMath::Vector3* inter)
{
	//オブジェクトのローカル座標系でのレイを得る
	Ray localRay;
	AliceMath::Vector4 tmp = { ray.start.x,ray.start.y,ray.start.z,1.0f };
	tmp = AliceMath::Vector4Trns(tmp, invMatWorld);
	localRay.start = { tmp.x,tmp.y,tmp.z };
	localRay.dir = AliceMath::Vector3Trns(ray.dir, invMatWorld);
	localRay.dir.normalization();

	//ローカル座標系で交差をチェック
	std::vector<Triangle>::const_iterator it = triangle.cbegin();

	for (; it != triangle.cend(); ++it)
	{
		const Triangle& triangle_ = *it;
		AliceMath::Vector3 templnter;

		//レイと三角形の当たり判定
		if (Collision::CheckRay2Triangle(localRay, triangle_, nullptr, &templnter))
		{
			AliceMath::Matrix4& matWorld = GetModel()->GetMatWorld();
			//ワールド座標での交点を得る
			tmp = { templnter.x,templnter.y,templnter.z,1.0f };
			tmp = AliceMath::Vector4Trns(tmp, matWorld);
			templnter = { tmp.x,tmp.y,tmp.z };

			if (distance)
			{
				//交点とレイ始点の距離を計算
				AliceMath::Vector3 sub = templnter - ray.start;
				*distance = sub.dot(ray.dir);
			}

			if (inter)
			{
				*inter = templnter;
			}

			return true;
		}
	}

	return false;
}

void MeshCollider::SetAttribute(uint16_t attribute_)
{
	attribute = attribute_;
}

void MeshCollider::AddAttribute(uint16_t attribute_)
{
	attribute |= attribute_;
}

void MeshCollider::RemoveAttribute(uint16_t attribute_)
{
	attribute &= !attribute_;
}
