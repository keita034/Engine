#pragma once
#include"ModelInterface.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"Input.h"
#include"AliceMath.h"

class Player
{
private:
	ModelInterface* model = nullptr;
	Input* input = nullptr;
	AliceMath::Vector3 move = {0,0,0};
	AliceMath::Vector3 rot;

	//接地フラグ
	bool onGround = true;
	char PADDING2[3]{};
	//落下ベクトル
	AliceMath::Vector3 fallV;

	//コピーコンストラクタ・代入演算子削除
	Player& operator=(const Player&) = delete;
	Player(const Player&) = delete;
public:

	Player() = default;
	~Player() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void DrawModel(Camera* camera);
};

