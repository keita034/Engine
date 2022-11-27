#include"ModelMesh.h"
#include<atldef.h>
void ModelMesh::CreateBuffer()
{
	//頂点バッファ生成
	//全体のサイズ計算
	size_t size = vertices.size();
	//一つ分のサイズ計算
	size_t stride = sizeof(PosNormUvTangeCol);
	//生成
	vertexBuffer = std::make_shared<ComputeVertexBuffer>();
	vertexBuffer->Create(size, stride);
	if (!vertexBuffer->IsValid())
	{
		printf("頂点バッファの生成に失敗\n");
		return;
	}

	//インデックスバッファ生成
	//全体のサイズ計算
	size = indices.size();
	uint32_t* indice = indices.data();
	//生成
	indexBuffer = std::make_shared<IndexBuffer>();
	indexBuffer->Create(size, indice);
	if (!indexBuffer->IsValid())
	{
		printf("インデックスバッファの生成に失敗\n");
		return;
	}

	materialBuffer = std::make_shared<ConstantBuffer>();
	materialBuffer->Create(sizeof(ModelMaterial));
	if (!materialBuffer->IsValid())
	{
		printf("マテリアル用定数バッファの生成に失敗\n");
		return;
	}

	computeInputBuff = std::make_shared<StructuredBuffer>();
	computeInputBuff->Create(vertices.size(),sizeof(PosNormUvTangeColSkin));
	if (!computeInputBuff->IsValid())
	{
		printf("コンピュートシェーダの入力用データバッファの生成に失敗\n");
		return;
	}

	boneBuffer = std::make_shared<ConstantBuffer>();
	boneBuffer->Create(sizeof(SkinData));
	if (!boneBuffer->IsValid())
	{
		printf("コンピュートシェーダの定数バッファの生成に失敗\n");
		return;
	}

	// 変換行列の登録
	materialBuffer->Update(&material);

	skinComputeInput.vertices.resize(vertices.size());

	vertice.resize(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{

		vertice[i].position = vertices[i].position;
		vertice[i].normal = vertices[i].normal;
		vertice[i].uv = vertices[i].uv;
		vertice[i].tangent = vertices[i].tangent;
		vertice[i].color = vertices[i].color;

	}

	vertexBuffer->Update(vertice.data());
}

void ModelMesh::UpdateBoneMatrix(Node* aiNode, AliceMathF::Matrix4 matrix)
{
	static_cast<void>(aiNode);
	static_cast<void>(matrix);

}

void ModelMesh::FillComputeMatrix()
{

}



void ModelMesh::FillVertex()
{
	//GetSkinData(skinData);

	skinComputeInput.bone = skinData;

	boneBuffer->Update(skinComputeInput.bone.bones.data());

	computeInputBuff->Update(vertices.data());
}

void ModelMesh::ReadNodeHierarchy(float frame, const aiNode* pNode, const aiMatrix4x4 parentTransform,const aiAnimation* animation,const AliceMathF::Matrix4& inverseTransform)
{
	std::string nodeNameInf(pNode->mName.data);

	aiMatrix4x4 nodeTransform = pNode->mTransformation;

	const aiNodeAnim* nodeAnim = FindNodeAnim(animation, nodeNameInf);

	if (nodeAnim)
	{
		//scaling
		aiVector3D scaling_vector = calcInterpolatedScaling(frame, nodeAnim);
		aiMatrix4x4 scaling_matr;
		aiMatrix4x4::Scaling(scaling_vector, scaling_matr);

		//rotation
		aiQuaternion rotate_quat = CalcInterpolatedRotation(frame, nodeAnim);
		aiMatrix4x4 rotate_matr = aiMatrix4x4(rotate_quat.GetMatrix());

		//translation
		aiVector3D translate_vector = CalcInterpolatedPosition(frame, nodeAnim);
		aiMatrix4x4 translate_matr;
		aiMatrix4x4::Translation(translate_vector, translate_matr);

		if (std::string(nodeAnim->mNodeName.data) == std::string("Head"))
		{

			nodeTransform = translate_matr * (rotate_matr) * scaling_matr;
		}
		else
		{
			nodeTransform = translate_matr * rotate_matr * scaling_matr;
		}

	}

	aiMatrix4x4 global_transform = parentTransform * nodeTransform;


	if (bones.find(nodeNameInf) != bones.end())
	{
		UINT bone_index = bones[nodeNameInf].index;
		vecBones[bone_index].matrix = inverseTransform * global_transform * vecBones[bone_index].offsetMatirx;
	}

	for (UINT i = 0; i < pNode->mNumChildren; i++)
	{
		ReadNodeHierarchy(frame, pNode->mChildren[i], global_transform, animation, inverseTransform);
	}
}

aiVector3D ModelMesh::CalcInterpolatedPosition(float frame, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		return pNodeAnim->mPositionKeys[0].mValue;
	}

	UINT position_index = FindPosition(frame, pNodeAnim);
	UINT next_position_index = position_index + 1;
	assert(next_position_index < pNodeAnim->mNumPositionKeys);
	float delta_time = (float)(pNodeAnim->mPositionKeys[next_position_index].mTime - pNodeAnim->mPositionKeys[position_index].mTime);
	float factor = (frame - (float)pNodeAnim->mPositionKeys[position_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = pNodeAnim->mPositionKeys[position_index].mValue;
	aiVector3D end = pNodeAnim->mPositionKeys[next_position_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

UINT ModelMesh::FindPosition(float frame, const aiNodeAnim* pNodeAnim)
{
	for (UINT i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if (frame < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
		{
			return i; 
		}
	}

	assert(0);
	return 0;
}

aiQuaternion ModelMesh::CalcInterpolatedRotation(float frame, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1)
	{
		return pNodeAnim->mRotationKeys[0].mValue;
	}

	UINT rotation_index = FindRotation(frame, pNodeAnim);
	UINT next_rotation_index = rotation_index + 1;
	assert(next_rotation_index < pNodeAnim->mNumRotationKeys);

	float delta_time = (float)(pNodeAnim->mRotationKeys[next_rotation_index].mTime - pNodeAnim->mRotationKeys[rotation_index].mTime);
	float factor = (frame - (float)pNodeAnim->mRotationKeys[rotation_index].mTime) / delta_time;

	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion start_quat = pNodeAnim->mRotationKeys[rotation_index].mValue;
	aiQuaternion end_quat = pNodeAnim->mRotationKeys[next_rotation_index].mValue;

	return Nlerp(start_quat, end_quat, factor);
}

aiQuaternion ModelMesh::Nlerp(aiQuaternion quaternion1, aiQuaternion quaternion2, float t)
{
	//cout << a.w + a.x + a.y + a.z << endl;
	quaternion1.Normalize();
	quaternion2.Normalize();

	aiQuaternion result;
	float dot_product = 
		quaternion1.x * quaternion2.x +
		quaternion1.y * quaternion2.y +
		quaternion1.z * quaternion2.z +
		quaternion1.w * quaternion2.w;

	float one_minus_blend = 1.0f - t;

	if (dot_product < 0.0f)
	{
		result.x = quaternion1.x * one_minus_blend + t * -quaternion2.x;
		result.y = quaternion1.y * one_minus_blend + t * -quaternion2.y;
		result.z = quaternion1.z * one_minus_blend + t * -quaternion2.z;
		result.w = quaternion1.w * one_minus_blend + t * -quaternion2.w;
	}
	else
	{
		result.x = quaternion1.x * one_minus_blend + t * quaternion2.x;
		result.y = quaternion1.y * one_minus_blend + t * quaternion2.y;
		result.z = quaternion1.z * one_minus_blend + t * quaternion2.z;
		result.w = quaternion1.w * one_minus_blend + t * quaternion2.w;
	}

	return result.Normalize();
}

UINT ModelMesh::FindRotation(float frame, const aiNodeAnim* pNodeAnim)
{
	for (UINT i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (frame < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
		{
			return i;
		}
	}

	assert(0);
	return 0;
}

aiVector3D ModelMesh::calcInterpolatedScaling(float frame, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1)
	{
		return pNodeAnim->mScalingKeys[0].mValue;
	}

	UINT scaling_index = FindScaling(frame, pNodeAnim);
	UINT next_scaling_index = scaling_index + 1;
	assert(next_scaling_index < pNodeAnim->mNumScalingKeys);

	float delta_time = (float)(pNodeAnim->mScalingKeys[next_scaling_index].mTime - pNodeAnim->mScalingKeys[scaling_index].mTime);
	float  factor = (frame - (float)pNodeAnim->mScalingKeys[scaling_index].mTime) / delta_time;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = pNodeAnim->mScalingKeys[scaling_index].mValue;
	aiVector3D end = pNodeAnim->mScalingKeys[next_scaling_index].mValue;
	aiVector3D delta = end - start;

	return start + factor * delta;
}

UINT ModelMesh::FindScaling(float frame, const aiNodeAnim* pNodeAnim)
{
	for (UINT i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++)
	{
		if (frame < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
		{
			return i; 
		}
	}

	assert(0);
	return 0;
}

const aiNodeAnim* ModelMesh::FindNodeAnim(const aiAnimation* pAnimation, const std::string pNodeName)
{
	for (UINT i = 0; i < pAnimation->mNumChannels; i++)
	{
		const aiNodeAnim* node_anim = pAnimation->mChannels[i]; 
		if (std::string(node_anim->mNodeName.data) == pNodeName)
		{
			return node_anim;
		}
	}

	return nullptr;

}
void ModelMesh::BoneTransform(float frame, std::vector<AliceMathF::Matrix4>& transforms,const fbxAnimation* animation, const AliceMathF::Matrix4& inverseTransform)
{
	aiMatrix4x4 identity_matrix;

	aiAnimation* aiAnimation = animation->mAnimation->mAnimations[0];

	float time_in_ticks = frame * animation->ticksPerSecond;
	float animation_time = fmodf(time_in_ticks, static_cast<float>(aiAnimation->mDuration));

	ReadNodeHierarchy(animation_time, animation->mAnimation->mRootNode, identity_matrix, aiAnimation, inverseTransform);

	transforms.resize(vecBones.size());

	for (size_t i = 0; i < vecBones.size(); i++)
	{
		transforms[i] = vecBones[i].matrix.Transpose();
	}
}

void ModelMesh::GetSkinData(SkinData& data)
{

	size_t i = 0;

	for (auto itr = bones.begin(); itr != bones.end(); ++itr)
	{

		if (32 <= i)
		{
			return;
		}

		data.bones[i] = itr->second.matrix;

		i++;
	}
}

void ModelMesh::CopyResource()
{
	
}
void ModelMesh::Draw(ID3D12GraphicsCommandList* cmdList, Transform* transform, Light* light)
{
	D3D12_VERTEX_BUFFER_VIEW vbView = vertexBuffer->GetView();
	D3D12_INDEX_BUFFER_VIEW ibView = indexBuffer->GetView();

	for (TextureData texture : textures)
	{
		// 定数バッファビュー(CBV)の設定コマンド
		cmdList->SetGraphicsRootConstantBufferView(0, transform->GetconstBuff()->GetGPUVirtualAddress());
		cmdList->SetGraphicsRootConstantBufferView(1, materialBuffer->GetAddress());
		light->SetConstBufferView(cmdList, 2);

		// 頂点バッファビューの設定コマンド
		cmdList->IASetVertexBuffers(0, 1, &vbView);

		//インデックスバッファビューの設定コマンド
		cmdList->IASetIndexBuffer(&ibView);

		// SRVヒープの設定コマンド
		cmdList->SetDescriptorHeaps(1, texture.srvHeap.GetAddressOf());

		// SRVヒープの先頭にあるSRVをルートパラメータ2番に設定
		cmdList->SetGraphicsRootDescriptorTable(4, texture.gpuHandle);

		// 描画コマンド
		cmdList->DrawIndexedInstanced(static_cast<UINT>(indices.size()), 1, 0, 0, 0);

		vertexBuffer->Transition(D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);

	}
}

void ModelMesh::UpdateBoneMatrix(aiNode* aiNode, AliceMathF::Matrix4 matrix)
{
	Bone* bone = &bones[aiNode->mName.C_Str()];

	AliceMathF::Matrix4 world;
	world = matrix;
	world *= bone->animationMatrix;

	bone->matrix = world;
	bone->matrix *= bone->offsetMatirx;

	for (unsigned int n = 0; n < aiNode->mNumChildren; n++)
	{
		UpdateBoneMatrix(aiNode->mChildren[n], world);
	}
}

void ModelMesh::Update(ComputeRelation* computeRelation)
{
	FillComputeMatrix();

	FillVertex();

	ID3D12GraphicsCommandList* cmdList = DirectX12Core::GetInstance()->GetCommandList().Get();

	//デスクプリタヒープをセット
	ID3D12DescriptorHeap* descriptorHeaps[] = {
		DirectX12Core::GetInstance()->GetDescriptorHeap()->GetHeap(),
	};
	cmdList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
	//ルートシグネチャをセット
	cmdList->SetComputeRootSignature(computeRelation->rootSignature->GetRootSignature());
	//パイプラインステートをセット
	cmdList->SetPipelineState(computeRelation->computePipelineState->GetPipelineState());

	cmdList->SetComputeRootDescriptorTable(0, computeInputBuff->GetAddress());
	cmdList->SetComputeRootConstantBufferView(1, boneBuffer->GetAddress());

	cmdList->SetComputeRootDescriptorTable(2, vertexBuffer->GetAddress());

	cmdList->Dispatch(256, 1, 1);

	CopyResource();
}

void  ModelMesh::DrawBgin()
{ 
	vertexBuffer->Transition(D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_GENERIC_READ);
};