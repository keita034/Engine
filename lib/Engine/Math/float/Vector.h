#pragma once
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

namespace AliceMathF
{
	const Vector4 operator+(const Vector3& v1, const Vector4& v2);

	/// <summary>
	/// Vector4をVector3に変換
	/// </summary>
	/// <param name="vec">変換するベクトル</param>
	/// <returns>Vector3</returns>
	Vector3 TrnsVec3(const Vector4& vec);

	/// <summary>
	/// Vector3をVector4に変換
	/// </summary>
	/// <param name="vec">変換するベクトル</param>
	/// <param name="matFlag">wを1にするかどうか</param>
	/// <returns>Vector4</returns>
	Vector4 TrnsVec4(const Vector3& vec, bool matFlag = false);

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector3 Vec3Mat4Mul(const Vector3& vec, const Matrix4& mat);

	/// <summary>
	/// ベクトルと行列の掛け算(W除算)
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector3& Vec3Mat4MulWdiv(const Vector3& vec, const Matrix4& mat);

	/// <summary>
	/// ベクトルと行列の掛け算
	/// </summary>
	/// <param name="vec">ベクトル</param>
	/// <param name="mat">行列</param>
	/// <returns>計算された値</returns>
	Vector4 Vec4Mat4Mul(const Vector4& vec, const Matrix4& mat);

	Vector3 Vector3Lerp(const Vector3& src1, const Vector3& src2, float t);
}