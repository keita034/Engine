#pragma once

#include"ErrorException.h"
#include"Model.h"
#include"ModelCreate.h"
#include"Camera.h"
#include"Collision.h"
#include"Input.h"
#include"SpriteCreat.h"
#include"ParticleCreat.h"
#include"Light.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Transform.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"

class GameScene
{
private:

	Mesh3D* mesh3D = nullptr;
	Input* input = nullptr;

	std::unique_ptr<Light> light;
	EngineMathF::Vector4 lightColor = { 1, 1, 1, 1 };

	std::unique_ptr<Camera> camera;

	std::unique_ptr<Particle> particle;


	//�r���{�[�h�ŕ`�悳���X�v���C�g
	std::unique_ptr<Sprite3D> spriteBillboard;

	Transform spriteBillboardTrans0;

	Transform spriteBillboardTrans1;

	Transform spriteBillboardTrans2;

	TextureData texData;

	char PADDING5[4]{};
	//================//

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

private:

	//�R�s�[�R���X�g���N�^�E������Z�q�폜
	GameScene& operator=(const GameScene&) = delete;
	GameScene(const GameScene&) = delete;
};