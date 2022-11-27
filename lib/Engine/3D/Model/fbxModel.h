#pragma once
#include"ModelMesh.h"
#include"fbxAnimation.h"
#include"StructuredBuffer.h"

//struct PosNormUvTangeCol
//{
//	AliceMathF::Vector3 position; // 位置座標
//	AliceMathF::Vector3 normal; // 法線
//	AliceMathF::Vector2 uv; // uv座標
//	AliceMathF::Vector3 tangent; // 接空間
//	AliceMathF::Vector4 color; // 頂点色
//};



class fbxModel :public Model
{

private:

	//モデル名
	std::string name;
	//ノード配列
	std::vector<ModelMesh> meshes;

	//フレンドクラス
	friend class FbxLoader;

	std::unique_ptr<ConstantBuffer> postureMatBuff;

	static std::shared_ptr<ComputeRelation> computeRelation;

	const aiScene* mScene = nullptr;

	std::vector<Node> nodes;

	float oldFrame = 0.0f;

	AliceMathF::Matrix4 globalInverseTransform;
	char PADING[4]{};

public:

	fbxModel() = default;
	~fbxModel() = default;

	virtual void Initialize();

	virtual void Draw(Transform* transform, Material* material = nullptr);

	void AnimationUpdate(const fbxAnimation* animation, float frame);

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <param name="filePath">オブジェクトまでのファイルパス</param>
	void Create(const char* filePath, bool smoothing, bool inverseU = false, bool inverseV = false, bool animeFlag = false);

private:

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create(const char* filePath, bool smoothing);
	virtual void Create(bool smoothing);
	virtual void Initialize(ModelShape shape);
	virtual void Initialize(const char* filePath, bool smoothing);
	//コピーコンストラクタ・代入演算子削除
	fbxModel& operator=(const fbxModel&) = delete;
	fbxModel(const fbxModel&) = delete;
};

