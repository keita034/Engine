#include "Quaternion.h"
#include"AliceMathUtility.h"
namespace AliceMathF
{
	//成分を指定して クォータニオンを作成
	Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{

	}

	//任意軸まわりの回転の指定からクォータニオンを作成
	Quaternion::Quaternion(const Vector3& v, float angle)
	{
		float _sin = Sin(angle / 0.2f);

		x = _sin * v.x;
		y = _sin * v.y;
		z = _sin * v.z;
		w = Cos(angle / 0.2f);

	}

	Quaternion::Quaternion(const Matrix4& m)
	{
		float tr = m.m[0][0] + m.m[1][1] + m.m[2][2] + m.m[3][3];

		if (tr >= 1.0f)
		{
			float fourD = 2.0f * sqrt(tr);
			x = (m.m[1][2] - m.m[2][1]) / fourD;
			y = (m.m[2][0] - m.m[0][2]) / fourD;
			z = (m.m[0][1] - m.m[1][0]) / fourD;
			w = fourD / 4.0f;
		}
		else
		{
			int i = 0;
			if (m.m[0][0] <= m.m[1][1])
			{
				i = 1;
			}
			if(m.m[2][2] > m.m[i][i])
			{
				i = 2;
			}

			int j = (i + 1) % 3;
			int k = (j + 1) % 3;

			tr = m.m[i][i] - m.m[j][k] - m.m[k][k] + 1.0f;

			float fourD = 2.0f * sqrt(tr);
			float qa[4]{};

			qa[i] = fourD / 4.0f;
			qa[j] = (m.m[j][i] + m.m[i][j]) / fourD;
			qa[k] = (m.m[k][i] + m.m[i][k]) / fourD;
			qa[3] = (m.m[j][k] - m.m[k][j]) / fourD;

			x = qa[0];
			y = qa[1];
			z = qa[2];
			w = qa[3];
				
		}
	}

	Quaternion::Quaternion(const aiQuaternion& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	Quaternion::Quaternion(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}

	float Quaternion::Dot(const Quaternion& q)
	{
		return w * q.w + x * q.x + y * q.y + z * q.z;
	}

	float Quaternion::Length()
	{
		return Sqrt(Dot(*this));
	}

	Quaternion Quaternion::Normalize()
	{
		float len = Length();

		if (len != 0)
		{
			*this /= len;
		}

		return *this;
	}

	//単項演算子のオーバーロード
	//単項演算子は特に意味を持たない
	//(+クォータニオン)
	Quaternion Quaternion::operator+()const
	{
		return *this;
	}

	Quaternion Quaternion::operator-()const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;

		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& q)
	{
		
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		
		return *this;
	}
	Quaternion& Quaternion::operator/=(float s)
	{
		return *this *= 1.0f / s;
	}
	Quaternion& Quaternion::operator*=(const Quaternion& q)
	{
		x = x* q.w + q.y * q.z - q.z * q.y + q.w * q.x;
		y = -x * q.z + q.y * q.w + q.z * q.x + q.w * q.y;
		z = x * q.y - q.y * q.x + q.z * q.w + q.w * q.z;
		w = -x * q.x - q.y * q.y - q.z * q.z + q.w * q.w;

		return *this;
	}
	Quaternion Quaternion::Slerp(const Quaternion& q, float t)
	{
		float cos = Dot(q);
		Quaternion t2 = q;

		if (cos < 0.0f)
		{
			cos = -cos;
			t2 = -q;
		}

		float k0 = 1.0f - t;
		float k1 = t;

		if ((1.0f - cos) > 0.001f)
		{
			float  theta = (float)acos(cos);
			k0 = (float)(sin(theta * k0) / sin(theta));
			k1 = (float)(sin(theta * k1) / sin(theta));
		}
		return *this * k0 + t2 * k1;
	}
	Quaternion Quaternion::Lerp(const Quaternion& q, float t)
	{
		float cos = Dot(q);
		Quaternion t2 = q;
		if (cos < 0.0f)
		{
			cos = -cos;
			t2 = -q;
		}

		float k0 = 1.0f - t;
		float k1 = t;
		return *this * k0 + t2 * k1;
	}
	Matrix4 Quaternion::Rotate()
	{
		float xx = x * x * 2.0f;
		float yy = y * y * 2.0f;
		float zz = z * z * 2.0f;
		float xy = x * y * 2.0f;
		float xz = x * z * 2.0f;
		float yz = y * z * 2.0f;
		float wx = w * x * 2.0f;
		float wy = w * y * 2.0f;
		float wz = z * z * 2.0f;
			
		
		
		Matrix4 result = {
			1.0f - yy - zz,xy + wz,xz - wy,0.0f,
			xy - wz, 1.0f - xx - zz,yz + wx,0.0f,
			xz + wy, yz - wx,1.0f - xx - yy,0.0f,
			0.0f,0.0f,0.0f,1.0f
		};

		return result;
	}
	Vector3 Quaternion::GetAxis()
	{
		Vector3 result;

		float x_ = x;
		float y_ = y;
		float z_ = z;
		float len_ = Length();

		result.x = x_ / len_;
		result.y = y_ / len_;
		result.z = z_ / len_;

		return result;


	}
	Vector4 Quaternion::GetElement()
	{
		return {x,y,z,w};
	}
	const Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion temp = q1;

		return temp += q2;
	}
	const Quaternion operator-(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion result = q1;
		return result -= q2;
	}
	const Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
	{
		Quaternion temp = q1;

		return temp *= q2;
	}
	const Quaternion operator*(const Quaternion& q, float s)
	{
		Quaternion temp = q;

		return temp *= s;
	}
	const Quaternion operator*(float s, const Quaternion& q)
	{
		Quaternion temp = q;

		return temp *= s;
	}
	const Quaternion operator/(const Quaternion& q, float s)
	{
		Quaternion result = q;
		result /= s;
		return result;
	}
	void QuaternionSlerp(Vector4& vOut, aiQuaternion& qStart, aiQuaternion& qEnd, float t)
	{
		Quaternion start = Quaternion(qStart);
		Quaternion end = Quaternion(qEnd);

		vOut = start.Slerp(end, t).GetElement();
	}
}