//#DirectXのやつ
#include"ErrorException.h"


//自作.h
#include"WindowsApp.h"
#include"Input.h"
#include"Controller.h"
#include"DirectX12Core.h"
#include"Mesh.h"
#include"3DMesh.h"
#include"Camera.h"
#include"GameScene.h"
#include"FPS.h"
#include"TextureManager.h"
#include"DefaultMaterial.h"
#include"AudioManager.h"
#include"FbxLoader.h"
#include"PostEffect.h"

//pragma comment


//using namespace

using namespace AliceMathF;

#ifdef _DEBUG
int main()
{
	HANDLE stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD consoleMode = 0;
	GetConsoleMode(stdOut, &consoleMode);
	consoleMode = consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(stdOut, consoleMode);
#else
#include<windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#endif


	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow();//ウィンドウ生成

	//DirectX初期化処理ここから

	DirectX12Core* DirectX12Core = DirectX12Core::GetInstance();//DirectX12Coreクラス読み込み
	DirectX12Core->DirectXInitialize();//DirectX12初期化
	DirectX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//背景の色変更(R,G,B,A)

	//DirectX初期化処理ここまで

	//描画初期化処理ここから
	Mesh* mesh = Mesh::GetInstance();
	Mesh3D* mesh3D = Mesh3D::GetInstance();

	TextureManager* textureManager = TextureManager::GetInstance();
	textureManager->Initialize();

	DefaultMaterial::GetDefaultMaterial()->Initialize();
	//描画初期化処理ここまで

	//その他初期化ここから

	AudioManager* audioManager = AudioManager::GetInstance();
	audioManager->Initialize();

	Input* input = Input::GetInstance();
	input->Initialize();

	FPS* fps = new FPS;

	FbxLoader::GetInstance()->Initialize();

	std::unique_ptr<PostEffect> postEffect = std::make_unique<PostEffect>();
	postEffect->PostInitialize();

	//その他初期化ここまで

	//シーンの初期化
	GameScene* gameScene = GameScene::GetInstance();
	gameScene->Initialize();

	//ゲームループ
	while (true)
	{
#ifdef _DEBUG
		//printf("\x1B[2J");
#endif
		fps->FpsControlBegin();

		if (!windowsApp->MessageWindow())//メッセージ処理
		{
			break;
		}

		//準備処理
		mesh->DrawReset();
		mesh3D->DrawReset();

		//DirectX毎フレーム処理　ここから

		//更新処理

		input->Update();
		audioManager->Update();

		gameScene->Update();

		//描画処理
		postEffect->PreDrawScen();

		gameScene->Draw();

		postEffect->PostDrawScen();

		DirectX12Core->BeginDraw();//描画準備
		postEffect->PostDraw();
		//DirectX毎フレーム処理　ここまで

		DirectX12Core->EndDraw();//描画後処理

		if (input->TriggerPush(DIK_ESCAPE))
		{
			break;
		}

		fps->FpsControlEnd();
	}

	FbxLoader::GetInstance()->Finalize();
	windowsApp->Break();
	DirectX12Core->Destroy();
	mesh->Destroy();
	mesh3D->Destroy();
	textureManager->Destroy();
	audioManager->Destroy();
	delete fps;
	return 0;
}