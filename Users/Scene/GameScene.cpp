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

	//���C�g������
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//���f���Ƀ��C�g���Z�b�g
	Model::SetLight(light.get());

	camera = std::make_unique<Camera>();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);
}

void GameScene::Update()
{
	//���C�g�̌��������ݒ�
	EngineMathF::Vector3 rightDir = { 10.0f,3.0f,5.0f };
	light->SetLightDir(rightDir);
	light->Update();
}

void GameScene::Draw()
{
}

GameScene* GameScene::GetInstance()
{
	static GameScene instance;
	return &instance;
}