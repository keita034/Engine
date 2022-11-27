#pragma once

#include"ErrorException.h"
#include"Camera.h"
#include"Sprite2D.h"
#include"Sprite3D.h"
#include"Collision.h"
#include"Input.h"
#include"BasicParticle.h"
#include"RainParticle.h"
#include"ParticleEmitter.h"
#include"Light.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Transform.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"
#include"Button.h"
#include"Cursor.h"
#include"fbxModel.h"
#include"fbxAnimation.h"
#include"FbxLoader.h"
#include"objModel.h"
#include"PrimitiveModel.h"

class GameScene
{
private:

	enum Scene
	{
		Particle,//�p�[�e�B�N��
		PolygonEffect,//�|���S������
	};

	Mesh* mesh2D = nullptr;
	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;

	std::unique_ptr<Light> light;
	AliceMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<Camera> camera;

	std::unique_ptr<BasicParticle> particle;
	std::unique_ptr<RainParticle> rainParticle;

	std::unique_ptr<ParticleEmitter> particleEmitter1;
	std::unique_ptr<ParticleEmitter> particleEmitter2;

	TextureData particleTex;

	TextureData grassTex;
	std::unique_ptr<Sprite3D> grassSprite;
	std::array<std::unique_ptr<Transform>, 20> grassTrans;

	TextureData texture;
	std::unique_ptr<Sprite3D> sprite;
	std::array<std::unique_ptr<Transform>, 2> spriteTrans;

	std::unique_ptr<objModel> model;
	Transform modelTrans;

	Scene scene = Particle;


	bool explosionFlag = false;
	float flame = 0.0f;

public:

	GameScene();
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//�Q�b�^�[
	static GameScene* GetInstance();

	void CameraMove();

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};