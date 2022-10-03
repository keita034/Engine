#include "Transform.h"
#include"DirectX12Core.h"

void Transform::Initialize()
{
	//�萔�o�b�t�@����(3D���W�ϊ��s��)
	DirectX12Core::GetInstance()->CreateConstBuff(constBuffMap, constBuff);

}

void Transform::TransUpdate(Camera* camera)
{
	EngineMathF::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//���[���h�s��̍���
	//�ό`�����Z�b�g
	matWorld = EngineMathF::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent)
	{
		matWorld *= parent->matWorld;
	}

	//�萔�o�b�t�@�ɏ�������
	constBuffMap->matWorld = matWorld * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
	constBuffMap->world = matWorld;
	constBuffMap->cameraPos = camera->eye;
}

void Transform::MakeWorldMatrix()
{
	EngineMathF::Matrix4 matScale, matRot, matTrans;

	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale.MakeScaling(scale);
	matRot.MakeRotation(rotation);
	matTrans.MakeTranslation(translation);

	//���[���h�s��̍���
	//�ό`�����Z�b�g
	matWorld = EngineMathF::MakeIdentity();
	//���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matScale;
	//���[���h�s��ɉ�]�𔽉f
	matWorld *= matRot;
	//���[���h�s��ɕ��s�ړ��𔽉f
	matWorld *= matTrans;
	//�e�s��̎w�肪����ꍇ�́A�|���Z����
	if (parent)
	{
		matWorld *= parent->matWorld;
	}
}

ID3D12Resource* Transform::GetconstBuff()
{
	return constBuff.Get();
}

worldViewpojCamera* Transform::GetWorldViewpojCamera()
{
	return constBuffMap;
}

namespace EngineMathF
{
	Matrix4 MakeWorldMatrix4(Transform & transform)
	{

		Matrix4 matWorld = MakeIdentity();

		Matrix4 matScal, matRot, matTrans;

		//�X�P�[�����O�{��
		matScal.MakeScaling(transform.scale);

		//��]�s��
		matRot.MakeRotation(transform.rotation);

		// matWorld_�Ɉړ��ʂ��|���Z
		matTrans.MakeTranslation(transform.translation);

		matWorld = matScal * matRot * matTrans;

		if (transform.parent)
		{
			matWorld *= transform.parent->matWorld;
		}

		return matWorld;
	}

	Vector3 GetWorldPosition(Transform & transform)
	{
		//���[���h���W������ϐ�
		Vector3 worldPos;
		//���[���h�s��̕��s�ړ��������擾(���[���h���W)
		worldPos.x = transform.matWorld.m[3][0];
		worldPos.y = transform.matWorld.m[3][1];
		worldPos.z = transform.matWorld.m[3][2];

		return worldPos;
	}
}