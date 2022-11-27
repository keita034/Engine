#include "DefaultMaterial.h"

void DefaultMaterial::Initialize()
{
	CreateDefaultTexture();

	CreateDefaultTextureMaterial();

	CreateDefaultLambertMaterial();

	CreateDefaultPhongMaterial();

	CreateDefaultSprite2DMaterial();

	CreateDefaultSprite3DMaterial();

	CreateDefaultFbxMaterial();

	CreateDefaultPostEffectMaterial();

	CreateDefaultParticleMaterial();

	CreateDefaultRainParticleMaterial();
}

DefaultMaterial* DefaultMaterial::GetDefaultMaterial()
{
	static DefaultMaterial material;
	return &material;
}

void DefaultMaterial::CreateDefaultTexture()
{
	
	DEFAULT_TEXTURE = TextureManager::Load("Resources/Default/white1x1.png");
}

void DefaultMaterial::CreateDefaultTextureMaterial()
{
	DEFAULT_TEXTURE_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_TEXTURE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_TEXTURE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/ModelBasicVS.hlsl");

	//ジオメトリシェーダの読み込み
	DEFAULT_TEXTURE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->geometryShader->Create("Resources/Shaders/3D/Model/PolygonEffectGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//ピクセルシェーダの読み込み
	DEFAULT_TEXTURE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_TEXTURE_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/ModelBasicPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//頂点レイアウト設定
	DEFAULT_TEXTURE_MATERIAL->inputLayouts = {
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//法線
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//ルートシグネチャ設定
	DEFAULT_TEXTURE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_TEXTURE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//ブレンド設定
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_TEXTURE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	//生成
	DEFAULT_TEXTURE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultLambertMaterial()
{
	DEFAULT_LAMBERT_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_LAMBERT_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_LAMBERT_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_LAMBERT_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/LambertVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_LAMBERT_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_LAMBERT_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/LambertPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//頂点レイアウト設定
	DEFAULT_LAMBERT_MATERIAL->inputLayouts = {
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//法線
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//ルートシグネチャ設定
	DEFAULT_LAMBERT_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_LAMBERT_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//ブレンド設定
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_LAMBERT_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	//生成
	DEFAULT_LAMBERT_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultPhongMaterial()
{
	DEFAULT_PHONG_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_PHONG_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_PHONG_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_PHONG_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/PhongVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_PHONG_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_PHONG_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/PhongPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//頂点レイアウト設定
	DEFAULT_PHONG_MATERIAL->inputLayouts = DEFAULT_TEXTURE_MATERIAL->inputLayouts;

	//ルートシグネチャ設定
	DEFAULT_PHONG_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_PHONG_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_PHONG_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_PHONG_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//ブレンド設定
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_PHONG_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	//生成
	DEFAULT_PHONG_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultSprite2DMaterial()
{
	//頂点シェーダの読み込み
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/SpriteVS.hlsl");

	//ピクセルシェーダの読み込み
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/SpritePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_SPRITE2D_MATERIAL[0].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[1].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[2].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[3].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[4].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE2D_MATERIAL[5].reset(CreateDefaultSprite2DBlend(BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultSprite3DMaterial()
{
	//頂点シェーダの読み込み
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/SpriteVS.hlsl");

	//ピクセルシェーダの読み込み
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/SpritePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_SPRITE3D_MATERIAL[0].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[1].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[2].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[3].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[4].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_SPRITE3D_MATERIAL[5].reset(CreateDefaultSprite3DBlend(BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultFbxMaterial()
{
	DEFAULT_FBX_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_FBX_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_FBX_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_FBX_MATERIAL->vertexShader->Create("Resources/Shaders/3D/Model/ModelSimpleVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_FBX_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_FBX_MATERIAL->pixelShader->Create("Resources/Shaders/3D/Model/ModelSimplePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//頂点レイアウト設定
	DEFAULT_FBX_MATERIAL->inputLayouts = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float3のPOSITION
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float3のNORMAL
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float2のTEXCOORD
	{ "TANGENT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float3のTANGENT
	{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }, // float4のCOLOR
	};

	//ルートシグネチャ設定
	DEFAULT_FBX_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 1);//b1
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 2);//b2
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 3);//b3
	DEFAULT_FBX_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_FBX_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_FBX_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());
	//生成
	DEFAULT_FBX_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultParticleMaterial()
{
	DEFAULT_PARTICLE_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_PARTICLE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_PARTICLE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->vertexShader->Create("Resources/Shaders/2D/ParticleVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_PARTICLE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->pixelShader->Create("Resources/Shaders/2D/ParticlePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_PARTICLE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_PARTICLE_MATERIAL->geometryShader->Create("Resources/Shaders/2D/ParticleGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//頂点レイアウト設定
	DEFAULT_PARTICLE_MATERIAL->inputLayouts = {
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//カラー
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//スケール
		{ "SCALE", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//回転角
		{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},

	};

	//ルートシグネチャ設定
	DEFAULT_PARTICLE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_PARTICLE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//ブレンド設定
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	DEFAULT_PARTICLE_MATERIAL->primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	DEFAULT_PARTICLE_MATERIAL->depthFlag = false;

	//生成
	DEFAULT_PARTICLE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultMeshMaterial()
{
	//頂点シェーダの読み込み
	std::unique_ptr<Shader>vertexShader = std::make_unique<Shader>();
	vertexShader->Create("Resources/Shaders/2D/MeshVS.hlsl");

	//ピクセルシェーダの読み込み
	std::unique_ptr<Shader>pixelShader = std::make_unique<Shader>();
	pixelShader->Create("Resources/Shaders/2D/MeshPS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	//三角形形状用パイプラインセット
	DEFAULT_MESH_MATERIAL[0].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(),pixelShader.get()));
	DEFAULT_MESH_MATERIAL[1].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[2].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[3].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[4].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_MESH_MATERIAL[5].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));

	//ライン形状用パイプラインセット
	DEFAULT_LINE_MATERIAL[0].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_NOBLEND, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[1].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ALPHA, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[2].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_ADD, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[3].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_SUB, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[4].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_MULA, vertexShader.get(), pixelShader.get()));
	DEFAULT_LINE_MATERIAL[5].reset(CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE, BlendMode::AX_BLENDMODE_INVSRC, vertexShader.get(), pixelShader.get()));
}

void DefaultMaterial::CreateDefaultRainParticleMaterial()
{
	DEFAULT_RAIN_PARTICLE_MATERIAL = std::make_unique<Material>();

	//テクスチャデータ設定
	DEFAULT_RAIN_PARTICLE_MATERIAL->textureData = DEFAULT_TEXTURE;

	//頂点シェーダの読み込み
	DEFAULT_RAIN_PARTICLE_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->vertexShader->Create("Resources/Shaders/2D/RainParticleVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_RAIN_PARTICLE_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->pixelShader->Create("Resources/Shaders/2D/RainParticlePS.hlsl", "main", "ps_5_0", Shader::ShaderType::PS);

	DEFAULT_RAIN_PARTICLE_MATERIAL->geometryShader = std::make_unique<Shader>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->geometryShader->Create("Resources/Shaders/2D/RainParticleGS.hlsl", "main", "gs_5_0", Shader::ShaderType::GS);

	//頂点レイアウト設定
	DEFAULT_RAIN_PARTICLE_MATERIAL->inputLayouts = {
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//カラー
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//スケール
		{ "SCALE", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//回転角
		{ "ROTATION", 0, DXGI_FORMAT_R32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},

	};

	//ルートシグネチャ設定
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_RAIN_PARTICLE_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//ブレンド設定
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_RAIN_PARTICLE_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	DEFAULT_RAIN_PARTICLE_MATERIAL->primitiveType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	DEFAULT_RAIN_PARTICLE_MATERIAL->depthFlag = false;

	//生成
	DEFAULT_RAIN_PARTICLE_MATERIAL->Initialize();
}

void DefaultMaterial::CreateDefaultPostEffectMaterial()
{
	DEFAULT_POST_EFFECT_MATERIAL = std::make_unique<Material>();

	//頂点シェーダの読み込み
	DEFAULT_POST_EFFECT_MATERIAL->vertexShader = std::make_unique<Shader>();
	DEFAULT_POST_EFFECT_MATERIAL->vertexShader->Create("Resources/Shaders/2D/PostEffectTestVS.hlsl");

	//ピクセルシェーダの読み込み
	DEFAULT_POST_EFFECT_MATERIAL->pixelShader = std::make_unique<Shader>();
	DEFAULT_POST_EFFECT_MATERIAL->pixelShader->Create("Resources/Shaders/2D/PostEffectTestPS.hlsl","main","ps_5_0");

	//頂点レイアウト設定
	DEFAULT_POST_EFFECT_MATERIAL->inputLayouts =
	{
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//カラー
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	DEFAULT_POST_EFFECT_MATERIAL->depthFlag = false;
	
	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	DEFAULT_POST_EFFECT_MATERIAL->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値

	//ルートシグネチャ設定
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature = std::make_unique<RootSignature>();
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Add(RootSignature::RangeType::SRV, 1);//t1
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->AddStaticSampler(0);//s0
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->AddStaticSampler(1);//s1
	DEFAULT_POST_EFFECT_MATERIAL->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//生成
	DEFAULT_POST_EFFECT_MATERIAL->Initialize();
}

Material* DefaultMaterial::CreateDefaultMeshBlend(D3D12_PRIMITIVE_TOPOLOGY_TYPE type, BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

	//頂点シェーダの読み込み
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//ピクセルシェーダの読み込み
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);

	//頂点レイアウト設定
	material->inputLayouts = {
		//座標
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//uv座標 
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	material->depthFlag = false;

	material->primitiveType = type;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// デストからソースを減算
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-デストカラーの値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// 使わない
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//ルートシグネチャ設定
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());
	//生成
	material->Initialize();
	
	return material;
}

Material* DefaultMaterial::CreateDefaultSprite2DBlend(BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

	//頂点シェーダの読み込み
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//ピクセルシェーダの読み込み
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);

	//頂点レイアウト設定
	material->inputLayouts =
	{
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//カラー
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	material->depthFlag = false;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// デストからソースを減算
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-デストカラーの値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// 使わない
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//ルートシグネチャ設定
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	material->rootSignature->AddStaticSampler(0);//s0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//生成
	material->Initialize();
	
	return material;
}

Material* DefaultMaterial::CreateDefaultSprite3DBlend(BlendMode mode, Shader* vex, Shader* pix)
{
	Material* material = new Material;

//頂点シェーダの読み込み
	material->vertexShader = std::make_unique<Shader>();
	material->vertexShader->Copy(vex);

	//ピクセルシェーダの読み込み
	material->pixelShader = std::make_unique<Shader>();
	material->pixelShader->Copy(pix);


	//頂点レイアウト設定
	material->inputLayouts =
	{
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//カラー
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

		material->blenddesc.AlphaToCoverageEnable = true;

	switch (mode)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:

		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;// 1.0f-ソースのアルファ値
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_REV_SUBTRACT;// デストからソースを減算
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースの値を100% 使う
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ONE;// デストの値を100% 使う
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ZERO;
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_SRC_COLOR;
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		material->blenddesc.RenderTarget[0].BlendEnable = true;// ブレンドを有効
		material->blenddesc.RenderTarget[0].SrcBlend = D3D12_BLEND_INV_DEST_COLOR;// 1.0f-デストカラーの値
		material->blenddesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;// 使わない
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		break;
	default:
		break;
	}

	//ルートシグネチャ設定
	material->rootSignature = std::make_unique<RootSignature>();
	material->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
	material->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0
	material->rootSignature->AddStaticSampler(0);//s0
	material->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

	//生成
	material->Initialize();

	return material;
}
