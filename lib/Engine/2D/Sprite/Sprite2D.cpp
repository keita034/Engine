#include "Sprite2D.h"
#include"WindowsApp.h"

void Sprite2D::Initialize(const TextureData& textureData)
{
	SpriteInitialize();

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().width);
	float height = static_cast<float>(WindowsApp::GetInstance()->GetWindowSize().height);

	AliceMathF::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);

	texture = textureData;

	trimmingRange.z = static_cast<float>(texture.width);
	trimmingRange.w = static_cast<float>(texture.height);

	CreatVertexIndexBuffer();
}

//描画
void Sprite2D::Draw(Transform& transform, BlendMode blend, Material* material)
{
	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * static_cast<float>(texture.width)) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * static_cast<float>(texture.width)) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * static_cast<float>(texture.height)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * static_cast<float>(texture.height)) * isFlipY;

	float texLeft = trimmingRange.x / static_cast<float>(texture.width);
	float texTop = trimmingRange.y / static_cast<float>(texture.height);
	float texRight = trimmingRange.z / static_cast<float>(texture.width);
	float texBottom = trimmingRange.w / static_cast<float>(texture.height);

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left,top,0.0f},{texLeft,texTop},{texture.color.x,texture.color.y,texture.color.z,texture.color.w}},//左上インデックス0
		{{left,bottom,0.0f},{texLeft,texBottom},{texture.color.x,texture.color.y,texture.color.z,texture.color.w}},//左下インデックス1
		{{right,top,0.0f},{texRight,texTop},{texture.color.x,texture.color.y,texture.color.z,texture.color.w}},//右上インデックス2
		{{right,bottom,0.0f},{texRight,texBottom},{texture.color.x,texture.color.y,texture.color.z,texture.color.w}},//右下インデックス3
	};

	// インデックスデータ
	uint32_t indices[] =
	{
		1, 0, 3, // 三角形1つ目
		2, 3, 0, // 三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	AliceMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;

	transform.Update();

	switch (blend)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[1].get();
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[2].get();
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[3].get();
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[4].get();
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[5].get();
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		printf("ブレンドの種類数を入れています");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("マテリアルがnullです");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("ブレンドの範囲外を入れています");
		assert(0);
		break;
	}

	SpriteDraw(transform, spriteMaterial);
}

void Sprite2D::AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend, Material* material)
{
	size_t animeFrame = static_cast<size_t>(frame / frameDiv);

	size_t width = static_cast<size_t>(radiusX) * 2;
	size_t height = static_cast<size_t>(radiusY) * 2;

	float texTop = trimmingRange.y / static_cast<float>(texture.height);
	float texRight = trimmingRange.z / static_cast<float>(texture.width);

	float widthU = static_cast<float>(width) / (texRight * static_cast<float>(texture.width));

	//画像の半分のサイズ

	if (texture.width / width < animeFrame + 1)
	{
		frame = 0;
	}

	float isFlipX, isFlipY;
	isFlipX = flipX ? -1.0f : 1.0f;
	isFlipY = flipY ? -1.0f : 1.0f;

	float left = ((0.0f - anchorPoint.x) * static_cast<float>(width)) * isFlipX;
	float right = ((1.0f - anchorPoint.x) * static_cast<float>(width)) * isFlipX;
	float top = ((0.0f - anchorPoint.y) * static_cast<float>(height)) * isFlipY;
	float bottom = ((1.0f - anchorPoint.y) * static_cast<float>(height)) * isFlipY;

	// 頂点データ
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{left, top, 0.0f},{widthU * static_cast<float>(animeFrame),texTop},{1.0f,1.0f,1.0f,1.0f}},//左上インデックス0
		{{left, bottom, 0.0f},{widthU * static_cast<float>(animeFrame),texRight},{1.0f,1.0f,1.0f,1.0f}},//左下インデックス1
		{{right, top, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texTop},{1.0f,1.0f,1.0f,1.0f}},//右上インデックス2
		{{right, bottom, 0.0f},{widthU * static_cast<float>((animeFrame + 1)),texRight},{1.0f,1.0f,1.0f,1.0f}},//右下インデックス3
	};

	// インデックスデータ
	uint32_t indices[] =
	{
		1, 0, 3, // 三角形1つ目
		2, 3, 0, // 三角形2つ目
	};

	//頂点バッファへのデータ転送
	vertexBuffer->Update(vertices);

	//インデックスバッファへのデータ転送
	indexBuffer->Update(indices);

	AliceMathF::Matrix4 mTrans, mRot, mScale, matWorld;
	//平行移動行列
	mTrans.MakeTranslation(transform.translation);
	//回転行列
	mRot.MakeRotation(transform.rotation);
	//スケール行列
	mScale.MakeScaling(transform.scale);
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

	transform.matWorld = matWorld * matProjection;

	transform.GetWorldViewpojCamera()->matWorld = transform.matWorld;
	transform.Update();

	switch (blend)
	{
	case BlendMode::AX_BLENDMODE_NOBLEND:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		break;
	case BlendMode::AX_BLENDMODE_ALPHA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[1].get();
		break;
	case BlendMode::AX_BLENDMODE_ADD:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[2].get();
		break;
	case BlendMode::AX_BLENDMODE_SUB:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[3].get();
		break;
	case BlendMode::AX_BLENDMODE_MULA:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[4].get();
		break;
	case BlendMode::AX_BLENDMODE_INVSRC:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[5].get();
		break;
	case BlendMode::AX_BLENDMODE_MAX:
		spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		printf("ブレンドの種類数を入れています");
		break;
	case BlendMode::AX_BLENDMODE_CUSTOM:
		if (material)
		{
			spriteMaterial = material;
		}
		else
		{
			printf("マテリアルがnullです");
			spriteMaterial = DefaultMaterial::GetDefaultMaterial()->DEFAULT_SPRITE2D_MATERIAL[0].get();
		}
		break;
	default:
		printf("ブレンドの範囲外を入れています");
		assert(0);
		break;
	}

	SpriteDraw(transform, spriteMaterial);
}
