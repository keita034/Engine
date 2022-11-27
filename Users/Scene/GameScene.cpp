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
	mesh2D = Mesh::GetInstance();

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	camera = std::make_unique<Camera>();
	camera->eye = { 0,3,-20 };
	camera->target = {0,3,0};
	camera->Initialize(UpdateProjMatrixFunc_Perspective);

	particle.reset(Particle::CreateParticle());

	particleTex = TextureManager::Load("Resources/Default/Particle/effect4.png");
	grassTex = TextureManager::Load("Resources/grass.png");
	texture = TextureManager::Load("Resources/Sprite.png");


	grassSprite.reset(Sprite::Create3DSprite(grassTex));

	rainParticle.reset(Particle::CreateRainParticle());

	for (size_t i = 0; i < grassTrans.size(); i++)
	{
		grassTrans[i] = std::make_unique<Transform>();
		grassTrans[i]->Initialize();

		grassTrans[i]->translation.x = static_cast<float>(rand()) / RAND_MAX * 8.0f - 8.0f / 2.0f;
		grassTrans[i]->translation.y = -3.0f;
		grassTrans[i]->translation.z = static_cast<float>(rand()) / RAND_MAX * 8.0f - 8.0f / 2.0f;


		grassTrans[i]->scale.x = 0.5f;
		grassTrans[i]->scale.y = 0.5f;
		grassTrans[i]->scale.z = 0.5f;
	}

	sprite.reset(Sprite::Create3DSprite(texture));

	for (size_t i = 0; i < spriteTrans.size(); i++)
	{
		spriteTrans[i] = std::make_unique<Transform>();
		spriteTrans[i]->Initialize();
		spriteTrans[i]->scale.x = 0.5f;
		spriteTrans[i]->scale.y = 0.5f;
		spriteTrans[i]->scale.z = 0.5f;
		spriteTrans[i]->translation.y = 1.0f;
	}
	spriteTrans[0]->translation.x = 2.0f;
	spriteTrans[1]->translation.x = -2.0f;

	particleEmitter1 = std::make_unique<ParticleEmitter>();
	particleEmitter1->Initialize();
	particleEmitter1->SetPosition({ -5,6,0 });
	particleEmitter1->SetScale({ 2.0f,0 });

	particleEmitter2 = std::make_unique<ParticleEmitter>();
	particleEmitter2->Initialize();
	particleEmitter2->SetPosition({ 5,6,0 });
	particleEmitter2->SetScale({ 2.0f,0 });
	particleEmitter2->SetEndColor({ 0,1,0,1 });
	particleEmitter2->SetStartColor({1,0,0,1});

	model.reset(Model::CreateObjModel("Resources/F-15"));
	modelTrans.Initialize();
	modelTrans.rotation.y = AliceMathF::AX_PI / 2;

}

void GameScene::Update()
{
	switch (scene)
	{
	case GameScene::Particle:
	{
		CameraMove();

		particleEmitter1->FireWorkUpdate();
		particleEmitter2->FireWorkUpdate();

		rainParticle->Update({ 0,20,0 }, { 100,100 }, { 0,0,0,1 }, 200);

		if (input->TriggerPush(DIK_R))
		{
			camera->eye = { 0,3,-20 };
			camera->target = { 0,3,0 };
		}
	}
		break;
	case GameScene::PolygonEffect:

		CameraMove();

		if (input->TriggerPush(DIK_SPACE))
		{
			explosionFlag = true;
			flame = 0.0f;
		}

		if (explosionFlag)
		{
			flame += 0.1f;
		}

		if (input->TriggerPush(DIK_R))
		{
			explosionFlag = false;
			flame = 0.0f;
		}

		break;
	}

	if (input->TriggerPush(DIK_1))
	{
		scene = Particle;
		camera->eye = { 0,3,-20 };
		camera->target = { 0,3,0 };
	}

	if (input->TriggerPush(DIK_2))
	{
		scene = PolygonEffect;
		camera->eye = { 0,0,-10 };
		camera->target = { 0,0,0 };
		explosionFlag = false;
		flame = 0.0f;
	}

	modelTrans.TransUpdate(camera.get());
}

void GameScene::Draw()
{

	switch (scene)
	{
	case GameScene::Particle:

		particleEmitter1->Draw(particleTex, camera.get());
		particleEmitter2->Draw(particleTex, camera.get());

		rainParticle->Draw(camera.get());

		for (size_t i = 0; i < grassTrans.size(); i++)
		{
			grassSprite->Draw(*grassTrans[i], camera.get(), BlendMode::AX_BLENDMODE_ALPHA, YBillboard);
		}


		sprite->Draw(*spriteTrans[0], camera.get(), BlendMode::AX_BLENDMODE_ALPHA, AllBillboard);
		sprite->Draw(*spriteTrans[1], camera.get());


		break;
	case GameScene::PolygonEffect:

		model->EffectDraw(&modelTrans, flame);
		break;
	default:
		break;
	}
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}

void GameScene::CameraMove()
{
	AliceMathF::Vector3 move = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.0f, 0.1f};
	}
	if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.0f, 0.1f};
	}

	if (input->KeepPush(DIK_A))
	{
		move += {0.1f, 0.0f, 0.0f};
	}
	if (input->KeepPush(DIK_D))
	{
		move -= {0.1f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_Z))
	{
		move += {0.0f, 0.1f, 0.0f};
		camera->target += {0.0f, 0.1f, 0.0f};
	}
	if (input->KeepPush(DIK_X))
	{
		move -= {0.0f, 0.1f, 0.0f};
		camera->target -= {0.0f, 0.1f, 0.0f};
	}

	if (input->KeepPush(DIK_UP))
	{
		move += {0.0f, 0.1f, 0.0f};
	}
	if (input->KeepPush(DIK_DOWN))
	{
		move -= {0.0f, 0.1f, 0.0f};
	}

	camera->eye += move;
}
