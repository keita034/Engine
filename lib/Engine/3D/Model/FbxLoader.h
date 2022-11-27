#pragma once
#include "ErrorException.h"
#include"AliceMathUtility.h"
#include"fbxModel.h"



class FbxLoader
{

private:

	//D3D12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;

	std::string directoryPath;

	bool anicmatrixion = false;

	bool inverseU = false;

	bool inverseV = false;
	char PADING[5] = {};

	const size_t MAX_BONE_INDICES = 4;

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	void LoadModel(fbxModel* model, const std::string& modelDirectory, bool inverseU_, bool inverseV_, bool animeFlag);

	void LoadAnimation(fbxAnimation* animation, const std::string& modelDirectory, const std::string& name);

private:

	void PraseNodeRecurive(fbxModel* model, aiNode* fbxNode, Node* parent = nullptr);

	void ParseMesh(fbxModel* model, aiMesh* fbxMesh);

	void ParseMeshVertices(fbxModel* model, aiMesh* mesh);

	void ParseMeshFaces(fbxModel* model, aiMesh* mesh);

	void ParseMaterial(fbxModel* model, aiMesh* mesh, aiMaterial* material);

	void GetNodeNum(const aiNode* node, UINT32& num);

	void ParseSkin(fbxModel* model, aiMesh* mesh);

	//テクスチャ解析
	std::vector<TextureData> LoadMatrixerialTextures(aiMaterial* cmatrix, aiTextureType type, std::string typeName, const aiScene* scene_);

	void PrintModelData(fbxModel* model);

	// ディレクトリを含んだファイルパスからファイル名を抽出する。
	std::string ExtractFileName(const std::string& path);

	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;
};