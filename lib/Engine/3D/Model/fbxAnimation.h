#pragma once
#include"ErrorException.h"
#include"Model.h"

class fbxAnimation
{
private:

	std::string name;

	const aiScene* mAnimation = nullptr;
	
	float ticksPerSecond = 0.0f;
	char PADING[4] = {};

	//フレンドクラス
	friend class FbxLoader;
	friend class fbxModel;
	friend class ModelMesh;

public:


private:


};