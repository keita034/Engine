#pragma once
#include"CollisionPrimitive.h"
#include"ErrorException.h"

class Collision
{

private:

public:

	/// <summary>
	/// 球と平面の当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="plane">平面</param>
	/// <param name="inter">交点(平面上の最近接点)</param>
	/// <returns>交差してるか</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// 球と球の当たり判定
	/// </summary>
	/// <param name="sphereA">球1</param>
	/// <param name="sphereB">球2</param>
	/// <param name="inter">交点(平面上の最近接点)</param>
	/// <returns>交差してるか</returns>
	static bool CheakSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, AliceMath::Vector3* inter = nullptr, AliceMath::Vector3* reject = nullptr);

	/// <summary>
	/// 点と三角形の最近接点を求める
	/// </summary>
	/// <param name="point">点</param>
	/// <param name="triangle">三角形</param>
	/// <param name="closest">最近接点(出力用)</param>
	static void ClosestPtPoint2Triangl(const AliceMath::Vector3& point,const Triangle& triangle, AliceMath::Vector3* closest);

	/// <summary>
	/// 球と法線付き三角形の当たりチェック
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="triangle">三角形</param>
	/// <param name="inter">交点(三角形上の最近接点)</param>
	/// <returns>交差しているか</returns>
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, AliceMath::Vector3* inter = nullptr, AliceMath::Vector3* reject = nullptr);

	/// <summary>
	/// レイと平面の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">平面</param>
	/// <param name="distance">距離(出力用)</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか</returns>
	static bool CheckRay2Plane(const Ray& ray,const Plane& plane,float* distance = nullptr, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// レイと三角形の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">三角形</param>
	/// <param name="distance">距離(出力用)</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか</returns>
	static bool CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance = nullptr, AliceMath::Vector3* inter = nullptr);

	/// <summary>
	/// レイと球の当たり判定
	/// </summary>
	/// <param name="ray">レイ</param>
	/// <param name="plane">球</param>
	/// <param name="distance">距離(出力用)</param>
	/// <param name="inter">交点(出力用)</param>
	/// <returns>交差しているか</returns>
	static bool CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance = nullptr, AliceMath::Vector3* inter = nullptr);
};

