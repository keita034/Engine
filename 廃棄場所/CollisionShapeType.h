#pragma once
/// <summary>
/// 衝突判定用関連の型定義
/// </summary>

enum CollisionShapeType
{
	ShapeUnknown = -1, // 未設定

	CollisionShapeSphere, // 球
	CollisionShapeMesh,//メッシュ
};