#include "GameScene.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	input = Input::GetInstance();

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	camera = std::make_unique<Camera>();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);

	camera->eye = { 0, 0, -150.0f };

	particle.reset(ParticleCreat::CreateParticle(L"Resources/Particle/effect3.png"));
	spriteBillboard.reset(SpriteCreat::Create3DSprite());
	spriteBillboard->Initialize();

	spriteBillboardTrans0.Initialize();

	spriteBillboardTrans0.translation = { 40.0f,0.0f,0.0f };
	spriteBillboardTrans0.rotation = { 0.0f,0.0f,0.0f };
	spriteBillboardTrans0.scale = { 0.5f,0.5f,0.5f };

	spriteBillboardTrans1.Initialize();
	spriteBillboardTrans1.translation = { -40.0f,0.0f,0.0f };
	spriteBillboardTrans1.rotation = { 0.0f,0.0f,0.0f };
	spriteBillboardTrans1.scale = { 0.5f,0.5f,0.5f };

	spriteBillboardTrans2.Initialize();
	spriteBillboardTrans2.translation = { 0.0f,0.0f,0.0f };
	spriteBillboardTrans2.rotation = { 0.0f,0.0f,0.0f };
	spriteBillboardTrans2.scale = { 0.5f,0.5f,0.5f };

	texData = TextureManager::GetInstance()->LoadTexture(L"Resources/Default/mario.jpg");
}

void GameScene::Update()
{
	//ライトの光線方向設定
	EngineMathF::Vector3 rightDir = { 10.0f,3.0f,5.0f };
	light->SetLightDir(rightDir);
	light->Update();

	EngineMathF::Vector3 move = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.0f, 0.5f};
	}
	else if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.0f, 0.5f};
	}

	if (input->KeepPush(DIK_A))
	{
		move += {0.5f, 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_D))
	{
		move -= {0.5f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_UP))
	{
		move += {0.0f, 0.5f, 0.0f};
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		move -= {0.0f, 0.5f, 0.0f};
	}

	camera->eye += move;


	spriteBillboardTrans0.TransUpdate(camera.get());
	spriteBillboardTrans1.TransUpdate(camera.get());
	spriteBillboardTrans2.TransUpdate(camera.get());

	for (size_t i = 0; i < 100; i++)
	{
		//X,Y,Z全て{-5.0f,+0.5f}でランダムに分布
		const float rnd_pos = 10.0f;
		EngineMathF::Vector3 pos{};
		pos.x = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//X,Y,Z全て{-0.05f,+0.05f}でランダムに分布
		const float rnd_vel = 0.1f;
		EngineMathF::Vector3 vel{};
		vel.x = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立てYのみ{-0.001f,0}でランダムに分布
		const float rnd_acc = 0.001f;
		EngineMathF::Vector3 acc{};
		acc.y = static_cast<float>(rand()) / RAND_MAX * rnd_acc;
		//スケール
		EngineMathF::Vector2 sca = { 1.0f,0.0f };
		//回転角
		EngineMathF::Vector2 rot = { EngineMathF::AX_PI / 3.0f,0.0f };
		//生存時間
		UINT life = 60 * rand() / RAND_MAX;
		//開始時カラー
		EngineMathF::Vector4 sCol = { 1.0f,0.0f,0.0f,1.0f };
		//終了カラー
		EngineMathF::Vector4 eCol = { 1.0f,1.0f,1.0f,1.0f };
		particle->Add(life, pos, vel, acc, sca, rot, sCol, eCol);
	}

	particle->Update();
}

void GameScene::Draw()
{
	//particle->Draw(camera.get());

	spriteBillboard->Draw(texData, spriteBillboardTrans0, camera.get(), AllBillboard);
	spriteBillboard->Draw(texData, spriteBillboardTrans1, camera.get(), XBillboard);
	spriteBillboard->Draw(texData, spriteBillboardTrans2);
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}