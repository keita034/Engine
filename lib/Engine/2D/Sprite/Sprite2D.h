#pragma once
#include"ErrorException.h"

#include"AliceMathUtility.h"
#include"Sprite.h"
#include"DefaultMaterial.h"
#include"AliceUtility.h"

class Sprite2D : public Sprite
{
private:


public:

	Sprite2D() = default;
	~Sprite2D() = default;
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textureData">テクスチャデータ</param>
	virtual void Initialize(const TextureData& textureData)override;

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="transform">ワールド変換データ</param>
	/// <param name="blend">ブレンド設定(初期値はアルファブレンド)</param>
	/// <param name="material">ブレンドがCUSTOM時に使う</param>
	virtual void Draw(Transform& transform,BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, Material* material = nullptr)override;

	/// <summary>
	/// アニメーション描画
	/// </summary>
	/// <param name="transform">ワールド変換データ</param>
	/// <param name="radiusX">アニメーション画像の一枚分の横幅</param>
	/// <param name="radiusY">アニメーション画像の一枚分の縦幅</param>
	/// <param name="frame">アニメーションフレーム</param>
	/// <param name="frameDiv">アニメーションフレームの最大値</param>
	/// <param name="blend">ブレンド設定(初期値はアルファブレンド)</param>
	/// <param name="material">ブレンドがCUSTOM時に使う</param>
	virtual void AnimationDraw(Transform& transform, uint16_t radiusX, uint16_t radiusY, float& frame, float frameDiv, BlendMode blend = BlendMode::AX_BLENDMODE_ALPHA, Material* material = nullptr)override;

private:


	//コピーコンストラクタ・代入演算子削除
	Sprite2D& operator=(const Sprite2D&) = delete;
	Sprite2D(const Sprite2D&) = delete;

};