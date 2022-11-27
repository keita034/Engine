#include "fbxModel.h"
#include"FbxLoader.h"

std::shared_ptr<ComputeRelation> fbxModel::computeRelation;


void fbxModel::Initialize()
{
	ModelInitialize();

	postureMatBuff = std::make_unique<ConstantBuffer>();

	postureMatBuff->Create(sizeof(AliceMathF::Matrix4));

	AliceMathF::Matrix4 tmp = AliceMathF::Matrix4();
	postureMatBuff->Update(&tmp);
}

void fbxModel::Draw(Transform* transform, Material* material)
{
	if (!material)
	{
		modelMaterialData = DefaultMaterial::GetDefaultMaterial()->DEFAULT_FBX_MATERIAL.get();
	}
	else
	{
		modelMaterialData = material;
	}

	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].DrawBgin();

		// プリミティブ形状の設定コマンド
		cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

		// パイプラインステートとルートシグネチャの設定コマンド
		cmdList->SetPipelineState(modelMaterialData->pipelineState->GetPipelineState());
		cmdList->SetGraphicsRootSignature(modelMaterialData->rootSignature->GetRootSignature());

		if (meshes[i].node)
		{
			postureMatBuff->Update(&meshes[i].node->globalTransform);
		}

		cmdList->SetGraphicsRootConstantBufferView(3, postureMatBuff->GetAddress());
		meshes[i].Draw(cmdList.Get(), transform, light);
	}
}

void fbxModel::AnimationUpdate(const fbxAnimation* animation, float frame)
{
	if (oldFrame == frame)
	{
		return;
	}

	oldFrame = frame;
	if (!animation)
	{
		return;
	}

	

	for (ModelMesh& m : meshes)
	{
		m.BoneTransform(frame, m.skinData.bones, animation, globalInverseTransform);

		m.Update(computeRelation.get());
	}
}

void fbxModel::Create(const char* filePath, bool smoothing, bool inverseU, bool inverseV, bool animeFlag)
{
	static_cast<void>(smoothing);

	FbxLoader::GetInstance()->LoadModel(this, filePath, inverseU, inverseV, animeFlag);

	//バッファ生成
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].CreateBuffer();
	}

	//計算シェーダー初期化
	//クラス共通で一回しか初期化しない
	if (!computeRelation)
	{
		//初期化
		computeRelation = std::make_shared<ComputeRelation>();

		//ルートシグネチャの初期化
		computeRelation->rootSignature = std::make_unique<RootSignature>();
		//ComputeShader用
		computeRelation->rootSignature->Add(RootSignature::RangeType::SRV, 0);//t0

		computeRelation->rootSignature->Add(RootSignature::RootType::CBV, 0);//b0
		//計算された頂点データ用
		computeRelation->rootSignature->Add(RootSignature::RangeType::UAV, 0);//u0
		//生成
		computeRelation->rootSignature->Create(DirectX12Core::GetInstance()->GetDevice().Get());

		//シェーダーの初期化
		computeRelation->computeShader = std::make_unique<Shader>();
		//シェーダー読み込み
		computeRelation->computeShader->Create("GpuSkinningCS.hlsl", "main", "cs_5_0", Shader::ShaderType::CS);

		//パイプラインステート初期化
		computeRelation->computePipelineState = std::make_shared<ComputePipelineState>();
		//シェーダーをセット
		computeRelation->computePipelineState->SetShader(*computeRelation->computeShader->GetShader());
		//ルートシグネチャのセット
		computeRelation->computePipelineState->SetRootSignature(computeRelation->rootSignature.get());
		//パイプラインステートの生成
		computeRelation->computePipelineState->Create(DirectX12Core::GetInstance()->GetDevice().Get());
	}
}

void fbxModel::Create(const char* filePath, bool smoothing)
{
	static_cast<void>(smoothing);
	static_cast<void>(filePath);
}

void fbxModel::Create(bool smoothing)
{
	static_cast<void>(smoothing);
}

void fbxModel::Initialize(ModelShape shape)
{
	static_cast<void>(shape);
}

void fbxModel::Initialize(const char* filePath, bool smoothing)
{
	static_cast<void>(smoothing);
	static_cast<void>(filePath);
}
