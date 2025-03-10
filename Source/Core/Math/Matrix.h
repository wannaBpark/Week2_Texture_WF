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
		return	M[0][0] * (
			M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
			M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			) -
			M[1][0] * (
				M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
				M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
				) +
			M[2][0] * (
				M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
				M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				) -
			M[3][0] * (
				M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
				M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
				M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				);
	}

	FMatrix Inverse() const
	{
		float Det = Determinant();
		if (Det == 0)
		{
			return FMatrix();
		}

		FMatrix Inv;
		float InvDet = 1.0f / Det;

		Inv.M[0][0] = InvDet * (
			M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
			M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			);

		Inv.M[0][1] = InvDet * (
			M[0][2] * (M[2][3] * M[3][1] - M[2][1] * M[3][3]) -
			M[0][3] * (M[2][2] * M[3][1] - M[2][1] * M[3][2]) +
			M[0][1] * (M[2][3] * M[3][2] - M[2][2] * M[3][3])
			);

		Inv.M[0][2] = InvDet * (
			M[0][3] * (M[1][2] * M[3][1] - M[1][1] * M[3][2]) -
			M[0][2] * (M[1][3] * M[3][1] - M[1][1] * M[3][3]) +
			M[0][1] * (M[1][3] * M[3][2] - M[1][2] * M[3][3])
			);

		Inv.M[0][3] = InvDet * (
			M[0][2] * (M[1][3] * M[2][1] - M[1][1] * M[2][3]) -
			M[0][3] * (M[1][2] * M[2][1] - M[1][1] * M[2][2]) +
			M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			);

		Inv.M[1][0] = InvDet * (
			M[1][2] * (M[2][3] * M[3][0] - M[2][0] * M[3][3]) -
			M[1][3] * (M[2][2] * M[3][0] - M[2][0] * M[3][2]) +
			M[1][0] * (M[2][3] * M[3][2] - M[2][2] * M[3][3])
			);

		Inv.M[1][1] = InvDet * (
			M[0][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][0] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
			M[3][0] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
			);

		Inv.M[1][2] = InvDet * (
			M[0][3] * (M[1][2] * M[3][0] - M[1][0] * M[3][2]) -
			M[0][2] * (M[1][3] * M[3][0] - M[1][0] * M[3][3]) +
			M[0][0] * (M[1][3] * M[3][2] - M[1][2] * M[3][3])
			);

		Inv.M[1][3] = InvDet * (
			M[0][2] * (M[1][3] * M[2][0] - M[1][0] * M[2][3]) -
			M[0][3] * (M[1][2] * M[2][0] - M[1][0] * M[2][2]) +
			M[0][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			);

		Inv.M[2][0] = InvDet * (
			M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]) -
			M[1][0] * (M[2][3] * M[3][1] - M[2][1] * M[3][3]) +
			M[1][1] * (M[2][3] * M[3][0] - M[2][0] * M[3][3])
			);

		Inv.M[2][1] = InvDet * (
			M[0][0] * (M[2][3] * M[3][1] - M[2][1] * M[3][3]) -
			M[2][0] * (M[0][3] * M[3][1] - M[0][1] * M[3][3]) +
			M[3][0] * (M[0][3] * M[2][1] - M[0][1] * M[2][3])
			);

		Inv.M[2][2] = InvDet * (
			M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
			M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
			M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
			);

		Inv.M[2][3] = InvDet * (
			M[0][0] * (M[1][3] * M[2][1] - M[1][1] * M[2][3]) -
			M[1][0] * (M[0][3] * M[2][1] - M[0][1] * M[2][3]) +
			M[2][0] * (M[0][3] * M[1][1] - M[0][1] * M[1][3])
			);

		Inv.M[3][0] = InvDet * (
			M[1][0] * (M[2][2] * M[3][1] - M[2][1] * M[3][2]) -
			M[2][0] * (M[1][2] * M[3][1] - M[1][1] * M[3][2]) +
			M[3][0] * (M[1][2] * M[2][1] - M[1][1] * M[2][2])
			);

		Inv.M[3][1] = InvDet * (
			M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
			M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
			M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
			);

		Inv.M[3][2] = InvDet * (
			M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
			M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
			M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
			);

		Inv.M[3][3] = InvDet * (
			M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
			M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
			M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
			);

		return Inv;

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

	static FMatrix Scale(FVector InScale)
	{
		return Scale(InScale.X, InScale.Y, InScale.Z);
	}

	static FMatrix RotateRoll(float Angle) //x�� ȸ��
	{
		Angle = FMath::DegreesToRadians(Angle);

		FMatrix Result;

		float C = cos(Angle);
		float S = sin(Angle);

		Result.M[1][1] = C; 
		Result.M[1][2] = -S;  
		Result.M[2][1] = S; 
		Result.M[2][2] = C;  

		return Result;
	}

	static FMatrix RotatePitch(float Angle) // y�� ȸ��
	{
		Angle = FMath::DegreesToRadians(Angle);

		FMatrix Result;

		float C = cos(Angle);
		float S = sin(Angle);

		Result.M[0][0] = C;  
		Result.M[0][2] = -S;  
		Result.M[2][0] = S; 
		Result.M[2][2] = C;  
		return Result;
	}

	static FMatrix RotateYaw(float Angle) // z�� ȸ��
	{
		Angle = FMath::DegreesToRadians(Angle);
		FMatrix Result;

		float C = cos(Angle);
		float S = sin(Angle);

		Result.M[0][0] = C;  // ù ��° ���� ù ��° ��
		Result.M[0][1] = -S;  // ù ��° ���� �� ��° ��
		Result.M[1][0] = S; // �� ��° ���� ù ��° ��
		Result.M[1][1] = C;  // �� ��° ���� �� ��° ��

		return Result;
	}

	static FMatrix Rotate(float X, float Y, float Z)
	{
		if (abs(Y) == 90)
		{
			return RotateRoll(X) * RotatePitch(Y) * RotateYaw(Z);		
		}
		return  RotateRoll(X) * RotateYaw(Z) * RotatePitch(Y);
		
	}

	static FMatrix Rotate(FVector Rotation)
	{
		return Rotate(Rotation.X, Rotation.Y, Rotation.Z);
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

