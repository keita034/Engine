#pragma once
#include"Model.h"
#include"DefaultMaterial.h"

class objModel : private Model
{
private:

public:

	objModel();
	~objModel();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void EffectDraw(Transform* transform, float velocity = 0.0f, Material* material = nullptr);

	virtual void Draw(Transform* transform, Material* material = nullptr)override;

	//初期化
	virtual void Initialize(const char* filePath, bool smoothing)override;

private:

	/// <summary>
	/// オブジェクト生成
	/// </summary>
	virtual void Create(const char* filePath, bool smoothing)override;

	virtual void Initialize(ModelShape shape);

	void LoadMaterial(const std::string& directoryPath,const std::string& filename);
	void LoadTexture(const std::string& directoryPath, const std::string& filename);

	virtual void Create(bool smoothing)override
	{
		static_cast<void>(smoothing);
	};

	void CalculateSmoothedVertexNormals();

	//コピーコンストラクタ・代入演算子削除
	objModel& operator=(const objModel&) = delete;
	objModel(const objModel&) = delete;
};