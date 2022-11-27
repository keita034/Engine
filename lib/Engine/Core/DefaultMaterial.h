#pragma once
#include"Material.h"
#include"TextureManager.h"
#include"AliceMathUtility.h"

class DefaultMaterial
{
public:

	//デフォルトのテクスチャ(白色)※改変しないこと
	TextureData DEFAULT_TEXTURE;

	//デフォルトのマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_TEXTURE_MATERIAL;

	//デフォルトのランバートマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_LAMBERT_MATERIAL;

	//デフォルトのフォングマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_PHONG_MATERIAL;

	//デフォルトのパーティクルマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_PARTICLE_MATERIAL;

	//デフォルトの雨パーティクルマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_RAIN_PARTICLE_MATERIAL;

	//デフォルトのスプライト2Dマテリアル※改変しないこと
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_SPRITE2D_MATERIAL;

	//デフォルトのスプライト3Dマテリアル※改変しないこと
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_SPRITE3D_MATERIAL;

	//デフォルトのFBXマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_FBX_MATERIAL;

	//デフォルトのポストエフェクトマテリアル※改変しないこと
	 std::unique_ptr<Material> DEFAULT_POST_EFFECT_MATERIAL;

	//デフォルトのスメッシュマテリアル※改変しないこと
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_MESH_MATERIAL;
	 std::array<std::unique_ptr<Material>, static_cast<size_t>(BlendMode::AX_BLENDMODE_MAX)> DEFAULT_LINE_MATERIAL;

	 void Initialize();

	 static DefaultMaterial* GetDefaultMaterial();

private:

	DefaultMaterial() = default;
	~DefaultMaterial() = default;

	 void CreateDefaultTexture();

	 void CreateDefaultTextureMaterial();

	 void CreateDefaultLambertMaterial();

	 void CreateDefaultPhongMaterial();

	 void CreateDefaultSprite2DMaterial();

	 void CreateDefaultSprite3DMaterial();

	 void CreateDefaultFbxMaterial();

	 void CreateDefaultParticleMaterial();

	 void CreateDefaultMeshMaterial();

	 void CreateDefaultRainParticleMaterial();

	 void CreateDefaultPostEffectMaterial();

	 Material* CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode, Shader* vex, Shader* pix);

	 Material* CreateDefaultSprite2DBlend(BlendMode mode, Shader* vex, Shader* pix);

	 Material* CreateDefaultSprite3DBlend(BlendMode mode, Shader* vex, Shader* pix);

	//コピーコンストラクタ・代入演算子削除
	 DefaultMaterial& operator=(const DefaultMaterial&) = delete;
	 DefaultMaterial(const DefaultMaterial&) = delete;
};
