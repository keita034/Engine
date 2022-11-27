#pragma once
#include"ErrorException.h"
#include"Vector4.h"
#include"Vector3.h"
#include"Matrix4.h"
namespace AliceMathF
{
	class Quaternion
	{
	public:
		float x;
		float y;
		float z;
		float w;

		//クオータニオンを作成
		Quaternion(float x = 0.0f, float y = 0.0f, float z = 9.0f, float w = 1.0f);
		Quaternion(const Vector3& v, float angle);
		Quaternion(const Matrix4& m);
		Quaternion(const aiQuaternion& q);
		Quaternion(const Vector4& v);

		//内積を求める
		float Dot(const Quaternion& q);

		//ノルムを求める
		float Length();
		//正規化する
		Quaternion Normalize();
		//単項演算子オーバーロード
		Quaternion operator + ()const;
		Quaternion operator - ()const;
		//代入演算子オーバーロード
		Quaternion& operator += (const Quaternion& q);
		Quaternion& operator -= (const Quaternion& q);
		Quaternion& operator *= (float s);
		Quaternion& operator /= (float s);
		Quaternion& operator *= (const Quaternion& q);

		Quaternion Slerp(const Quaternion& q, float t);
		Quaternion Lerp(const Quaternion& q, float t);
		Matrix4 Rotate();

		Vector3 GetAxis();

		Vector4 GetElement();
	};



	//2項演算子オーバーロード
	const Quaternion operator + (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator - (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q1, const Quaternion& q2);
	const Quaternion operator * (const Quaternion& q, float s);
	const Quaternion operator * (float s, const Quaternion& q);
	const Quaternion operator / (const Quaternion& q, float s);

	void QuaternionSlerp(Vector4& vOut, const aiQuaternion& qStart, const aiQuaternion& qEnd, float t);
}