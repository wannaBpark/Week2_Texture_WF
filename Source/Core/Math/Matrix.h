#pragma once
#include "Plane.h"
#include "Vector.h"


struct alignas(16) FMatrix
{
	float M[4][4];
	FMatrix()
	{
		// identity matrix
		M[0][0] = 1.0f; M[0][1] = 0.0f; M[0][2] = 0.0f; M[0][3] = 0.0f;
		M[1][0] = 0.0f; M[1][1] = 1.0f; M[1][2] = 0.0f; M[1][3] = 0.0f;
		M[2][0] = 0.0f; M[2][1] = 0.0f; M[2][2] = 1.0f; M[2][3] = 0.0f;
		M[3][0] = 0.0f; M[3][1] = 0.0f; M[3][2] = 0.0f; M[3][3] = 1.0f;
	}

	FMatrix(const FVector4& InX, const FVector4& InY, const FVector4& InZ, const FVector4& InW)
	{
		// row major
		M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
		M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
		M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
		M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
	}

	static FMatrix Identity()
	{
		return FMatrix();
	}

	static constexpr float PIDIV4 = PI / 4.0f;

	FMatrix operator+(const FMatrix& Other) const
	{
		FMatrix Result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Result.M[i][j] = M[i][j] + Other.M[i][j];
			}
		}
		return Result;
	}
	FMatrix operator+=(const FMatrix& Other)
	{
		*this = *this + Other;
		return *this;
	}
	FMatrix operator-(const FMatrix& Other) const
	{
		FMatrix Result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Result.M[i][j] = M[i][j] - Other.M[i][j];
			}
		}
		return Result;
	}
	FMatrix operator-=(const FMatrix& Other)
	{
		*this = *this - Other;
		return *this;
	}
	FMatrix operator*(const FMatrix& Other) const
	{
		FMatrix Result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Result.M[i][j] = M[i][0] * Other.M[0][j] +
					M[i][1] * Other.M[1][j] +
					M[i][2] * Other.M[2][j] +
					M[i][3] * Other.M[3][j];
			}
		}
		return Result;
	}
	FMatrix operator*=(const FMatrix& Other)
	{
		*this = *this * Other;
		return *this;
	}
	FMatrix operator*(float Other) const
	{
		FMatrix Result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Result.M[i][j] = M[i][j] * Other;
			}
		}
		return Result;
	}
	FMatrix operator*=(float Other)
	{
		*this = *this * Other;
		return *this;
	}
	bool operator==(const FMatrix& Other) const
	{
		bool bEqual = true;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (M[i][j] != Other.M[i][j])
				{
					bEqual = false;
					break;
				}
			}
		}
		
		return bEqual;
	}
	bool operator!=(const FMatrix& Other) const
	{
		return !(*this == Other);
	}

	FVector4 TransformVector4(const FVector4& Vector) const
	{
		return {
			Vector.X * M[0][0] + Vector.Y * M[1][0] + Vector.Z * M[2][0] + Vector.W * M[3][0],
			Vector.X * M[0][1] + Vector.Y * M[1][1] + Vector.Z * M[2][1] + Vector.W * M[3][1],
			Vector.X * M[0][2] + Vector.Y * M[1][2] + Vector.Z * M[2][2] + Vector.W * M[3][2],
			Vector.X * M[0][3] + Vector.Y * M[1][3] + Vector.Z * M[2][3] + Vector.W * M[3][3]
		};
	}

	FMatrix GetTransposed() const
	{
		FMatrix Result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Result.M[i][j] = M[j][i];
			}
		}
		return Result;
	}

	float Determinant() const
	{
		const float* m = &M[0][0];
		return 
			m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13])) -
			m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12])) +
			m[2] * (m[4] * (m[9]  * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9]  * m[12])) -
			m[3] * (m[4] * (m[9]  * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9]  * m[12]));
	}

	FMatrix Inverse() const
	{
		const float Det = Determinant();
		if (FMath::Abs(Det) < 1.0e-6f)
		{
			return {};
		}

		FMatrix Result;
		const float* m = &M[0][0];
		const float InvDet = 1.0f / Det;

		Result.M[0][0] = InvDet * (m[5]*(m[10]*m[15]-m[11]*m[14]) - m[6]*(m[9]*m[15]-m[11]*m[13]) + m[7]*(m[9]*m[14]-m[10]*m[13]));
		Result.M[0][1] = -InvDet * (m[1]*(m[10]*m[15]-m[11]*m[14]) - m[2]*(m[9]*m[15]-m[11]*m[13]) + m[3]*(m[9]*m[14]-m[10]*m[13]));
		Result.M[0][2] = InvDet * (m[1]*(m[6]*m[15]-m[7]*m[14]) - m[2]*(m[5]*m[15]-m[7]*m[13]) + m[3]*(m[5]*m[14]-m[6]*m[13]));
		Result.M[0][3] = -InvDet * (m[1]*(m[6]*m[11]-m[7]*m[10]) - m[2]*(m[5]*m[11]-m[7]*m[9]) + m[3]*(m[5]*m[10]-m[6]*m[9]));

		Result.M[1][0] = -InvDet * (m[4]*(m[10]*m[15]-m[11]*m[14]) - m[6]*(m[8]*m[15]-m[11]*m[12]) + m[7]*(m[8]*m[14]-m[10]*m[12]));
		Result.M[1][1] = InvDet * (m[0]*(m[10]*m[15]-m[11]*m[14]) - m[2]*(m[8]*m[15]-m[11]*m[12]) + m[3]*(m[8]*m[14]-m[10]*m[12]));
		Result.M[1][2] = -InvDet * (m[0]*(m[6]*m[15]-m[7]*m[14]) - m[2]*(m[4]*m[15]-m[7]*m[12]) + m[3]*(m[4]*m[14]-m[6]*m[12]));
		Result.M[1][3] = InvDet * (m[0]*(m[6]*m[11]-m[7]*m[10]) - m[2]*(m[4]*m[11]-m[7]*m[8]) + m[3]*(m[4]*m[10]-m[6]*m[8]));

		Result.M[2][0] = InvDet * (m[4]*(m[9]*m[15]-m[11]*m[13]) - m[5]*(m[8]*m[15]-m[11]*m[12]) + m[7]*(m[8]*m[13]-m[9]*m[12]));
		Result.M[2][1] = -InvDet * (m[0]*(m[9]*m[15]-m[11]*m[13]) - m[1]*(m[8]*m[15]-m[11]*m[12]) + m[3]*(m[8]*m[13]-m[9]*m[12]));
		Result.M[2][2] = InvDet * (m[0]*(m[5]*m[15]-m[7]*m[13]) - m[1]*(m[4]*m[15]-m[7]*m[12]) + m[3]*(m[4]*m[13]-m[5]*m[12]));
		Result.M[2][3] = -InvDet * (m[0]*(m[5]*m[11]-m[7]*m[9]) - m[1]*(m[4]*m[11]-m[7]*m[8]) + m[3]*(m[4]*m[9]-m[5]*m[8]));

		Result.M[3][0] = -InvDet * (m[4]*(m[9]*m[14]-m[10]*m[13]) - m[5]*(m[8]*m[14]-m[10]*m[12]) + m[6]*(m[8]*m[13]-m[9]*m[12]));
		Result.M[3][1] = InvDet * (m[0]*(m[9]*m[14]-m[10]*m[13]) - m[1]*(m[8]*m[14]-m[10]*m[12]) + m[2]*(m[8]*m[13]-m[9]*m[12]));
		Result.M[3][2] = -InvDet * (m[0]*(m[5]*m[14]-m[6]*m[13]) - m[1]*(m[4]*m[14]-m[6]*m[12]) + m[2]*(m[4]*m[13]-m[5]*m[12]));
		Result.M[3][3] = InvDet * (m[0]*(m[5]*m[10]-m[6]*m[9]) - m[1]*(m[4]*m[10]-m[6]*m[8]) + m[2]*(m[4]*m[9]-m[5]*m[8]));

		return Result;
	}

	static FMatrix Transpose(const FMatrix& Matrix)
	{
		FMatrix Result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				Result.M[i][j] = Matrix.M[j][i]; // ��� ���� �ٲ� ��ġ
			}
		}
		return Result;
	}

	static FMatrix Translate(float X, float Y, float Z)
	{
		FMatrix Result;
		Result.M[3][0] = X; 
		Result.M[3][1] = Y; 
		Result.M[3][2] = Z; 
		return Result;
	}

	static FMatrix Translate(FVector Translation)
	{
		return Translate(Translation.X, Translation.Y, Translation.Z);
	}

	static FMatrix Scale(float X, float Y, float Z)
	{
		FMatrix Result;
		Result.M[0][0] = X; 
		Result.M[1][1] = Y; 
		Result.M[2][2] = Z; 
		return Result;
	}

	static FMatrix Scale(const FVector& InScale)
	{
		return Scale(InScale.X, InScale.Y, InScale.Z);
	}

	static FMatrix Rotate(const FQuat& Q) 
	{
		FMatrix Result;

		float xx = Q.X * Q.X;
		float yy = Q.Y * Q.Y;
		float zz = Q.Z * Q.Z;
		float xy = Q.X * Q.Y;
		float xz = Q.X * Q.Z;
		float yz = Q.Y * Q.Z;
		float wx = Q.W * Q.X;
		float wy = Q.W * Q.Y;
		float wz = Q.W * Q.Z;

		Result.M[0][0] = 1.0f - 2.0f * (yy + zz);
		Result.M[0][1] = 2.0f * (xy - wz);
		Result.M[0][2] = 2.0f * (xz + wy);
		Result.M[0][3] = 0.0f;

		Result.M[1][0] = 2.0f * (xy + wz);
		Result.M[1][1] = 1.0f - 2.0f * (xx + zz);
		Result.M[1][2] = 2.0f * (yz - wx);
		Result.M[1][3] = 0.0f;

		Result.M[2][0] = 2.0f * (xz - wy);
		Result.M[2][1] = 2.0f * (yz + wx);
		Result.M[2][2] = 1.0f - 2.0f * (xx + yy);
		Result.M[2][3] = 0.0f;

		Result.M[3][0] = 0.0f;
		Result.M[3][1] = 0.0f;
		Result.M[3][2] = 0.0f;
		Result.M[3][3] = 1.0f;

		return Result;
	}
	/// <summary>
	/// 뷰 변환 행렬을 생성합니다.
	/// </summary>
	/// <param name="EyePosition">카메라의 포지션입니다.</param>
	/// <param name="FocusPoint">카메라가 바라보는 곳의 포지션입니다.</param>
	/// <param name="UpDirection">카메라의 위쪽 방향입니다.</param>
	/// <returns>뷰 변환 행렬을 반환합니다.</returns>
	static FMatrix LookAtLH(const FVector& EyePosition, const FVector& FocusPoint, const FVector& WorldUp)
	{
		FVector Forward = (FocusPoint - EyePosition).GetSafeNormal();
		FVector Right = FVector::CrossProduct(WorldUp, Forward).GetSafeNormal();
		FVector Up = FVector::CrossProduct(Forward, Right).GetSafeNormal();

		// row major
		FMatrix Result = FMatrix(
			FVector4(Right.X, Up.X, Forward.X, 0.0f),
			FVector4(Right.Y, Up.Y, Forward.Y, 0.0f),
			FVector4(Right.Z, Up.Z, Forward.Z, 0.0f), 
			FVector4(-Right.Dot(EyePosition), -Up.Dot(EyePosition), -Forward.Dot(EyePosition), 1.0f)                           
		);

		return Result;
	}
	static FMatrix PerspectiveFovLH(float FieldOfView, float AspectRatio, float NearPlane, float FarPlane)
	{
		FMatrix Result;
		float YScale = 1.0f / tan(FieldOfView / 2.0f);
		float XScale = YScale / AspectRatio;
		Result.M[0][0] = XScale;
		Result.M[1][1] = YScale;
		Result.M[2][2] = FarPlane / (FarPlane - NearPlane);
		Result.M[2][3] = 1.0f;
		Result.M[3][2] = -NearPlane * FarPlane / (FarPlane - NearPlane);
		Result.M[3][3] = 0.0f;
		return Result;
	}

	FVector GetTranslation() const
	{
		return FVector(M[3][0], M[3][1], M[3][2]);
	}

	FVector GetScale() const 
	{
		float X = FVector(M[0][0], M[0][1], M[0][2]).Length();
		float Y = FVector(M[1][0], M[1][1], M[1][2]).Length();
		float Z = FVector(M[2][0], M[2][1], M[2][2]).Length();
		return {X, Y, Z};
		
		//return FVector(M[0][0], M[1][1], M[2][2]);
	}

	FVector GetRotation() const 
	{
		FVector Result;
		Result.Y = asinf(-M[2][0]); // pitch
		if (cos(Result.Y) > 0.0001f) // not at gimbal lock
		{
			Result.X = atan2f(M[2][1], M[2][2]); // roll
			Result.Z = atan2f(M[1][0], M[0][0]); // yaw
		}
		else
		{
			Result.X = atan2f(-M[1][2], M[1][1]); // roll
			Result.Z = 0; // yaw
		}
		return Result;
	}

	class FTransform GetTransform() const;
	
};

