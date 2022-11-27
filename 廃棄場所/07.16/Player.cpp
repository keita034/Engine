#include "Player.h"
#include"SphereCollider.h"
#include"CollisionAttribute.h"
#include"RaycastHit.h"

void Player::Initialize()
{
	model = ModelCreate::CreateModel("Resources/player");
	input = Input::GetInstance();

	float radius = 0.6f;
	model->SetCollider(new SphereCollider(AliceMath::Vector4{ 0,radius ,0,0 },radius));
}

void Player::Update()
{

	//移動
	if (input->KeepPush(DIK_UP))
	{
		move.x -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		move.x += AliceMath::ChangeRadians(1.0f);
	}
	if (input->KeepPush(DIK_RIGHT))
	{
		move.z -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_LEFT))
	{
		move.z += AliceMath::ChangeRadians(1.0f);
	}
	//回転
	if (input->KeepPush(DIK_A))
	{
		rot.y -= AliceMath::ChangeRadians(1.0f);
	}
	else if (input->KeepPush(DIK_D))
	{
		rot.y += AliceMath::ChangeRadians(1.0f);
	}

	////落下処理
	//if (!onGround)
	//{
	//	//下向き加速度
	//	const float fallAcc = -0.01f;
	//	const float fallVYMin = -0.5f;
	//	//加速
	//	fallV.y = max(fallV.y + fallAcc, fallVYMin);
	//	//移動
	//	move.x += fallV.x;
	//	move.y += fallV.y;
	//	move.z += fallV.z;
	//}
	//else if (input->TriggerPush(DIK_SPACE))
	//{
	//	onGround = false;
	//	//ジャンプ時上向き初速
	//	const float jumpVYFist = 0.2f;
	//	fallV = { 0,jumpVYFist,0 };
	//}

	//model->Update(move, rot);

	////球コライダーを所得
	//SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(model->GetCollider());
	//assert(sphereCollider);

	////クエリーコールバッククラス定義
	//class PlayerQueryCallback :public QueryCallback
	//{
	//public:
	//	PlayerQueryCallback(Sphere* sphere) : sphere(sphere)
	//	{
	//	};
	//	~PlayerQueryCallback()
	//	{
	//	};
	//	virtual bool OnQueryHit(QueryHit& info)override
	//	{
	//		//ワールドの上方向
	//		const AliceMath::Vector4 up = { 0,1,0,0 };
	//		//排斥方向
	//		AliceMath::Vector4 rejectDir = info.reject.normalization();
	//		//上方向と排斥方向の角度差のコサイン値
	//		float cos_ = rejectDir.dot(up);

	//		//地面判定しきい値
	//		float threshold = std::cos(AliceMath::ChangeRadians(30.0f));
	//		//角度差によって天井または地面と判定される場合を覗いて
	//		if (-threshold < cos_ && cos_ < threshold)
	//		{
	//			//球を排斥(押し出す)
	//			sphere->center += info.reject;
	//			move += info.reject;
	//		}

	//		return true;
	//	}

	//	//クエリーに使用する球
	//	Sphere* sphere = nullptr;
	//	//排斥による移動量(累積値)
	//	AliceMath::Vector4 move = {};

	//};

	////クエリーコールバックの関数オブジェクト
	//PlayerQueryCallback callback(sphereCollider);

	////球と地形の交差を全検索
	//CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, CollisionAttrLandshape);
	////交差による排斥分動かす
	//move.x += callback.move.x;
	//move.y += callback.move.y;
	//move.z += callback.move.z;

	//model->Update(move, rot);

	////球の上端から球の下端までのレイキャスト用レイを準備
	//Ray ray;
	//ray.start = sphereCollider->center;
	//ray.start.y += sphereCollider->GetRadius();
	//ray.dir = { 0,-1,0,0 };
	//RaycastHit raycastHit;

	////設置状態
	//if (onGround)
	//{
	//	//スムーズに坂を下るための吸着距離
	//	const float adsDistace = 0.2f;
	//	//設置を維持
	//	if (CollisionManager::GetInstance()->Raycast(ray, CollisionAttrLandshape, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistace))
	//	{
	//		onGround = true;

	//		move.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
	//		model->Update(move, rot);
	//	}
	//	else
	//	{
	//		onGround = false;
	//		fallV = {};
	//	}
	//}
	//else if (fallV.y <= 0.0f)
	//{
	//	if (CollisionManager::GetInstance()->Raycast(ray, CollisionAttrLandshape, &raycastHit, sphereCollider->GetRadius() * 2.0f))
	//	{
	//		//着地
	//		onGround = true;
	//		move.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
	//		model->Update(move, rot);
	//	}
	//}

	model->Update(move, rot);
}


void Player::DrawModel(Camera* camera)
{
	camera->SetTarget(move.x, move.y, move.z);
	model->Draw(camera);
}
