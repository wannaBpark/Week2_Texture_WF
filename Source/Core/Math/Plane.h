#pragma once
#include "Vector.h"

#define PIDIV2 3.141592654/2

struct alignas(16) FVector4 : public FVector
{
    using FVector::X;
    using FVector::Y;
    using FVector::Z;

    float W;
    FVector4()
        : FVector(0, 0, 0), W(0)
    {
    }
    FVector4(float InX, float InY, float InZ, float InW)
        : FVector(InX, InY, InZ), W(InW)
    {
    }
};

struct alignas(16) Quaternion : public FVector4{
    using FVector::X;
    using FVector::Y;
    using FVector::Z;
    using FVector4::W;

    static Quaternion EulerToQuaternion(FVector Euler);
    static FVector QuaternionToEuler(const FVector4& quaternion);

    static FVector4 AddQuaternions(const FVector4& q1, const FVector4& q2);
    static FVector4 MultiplyQuaternions(const FVector4& q1, const FVector4& q2);
    static FVector4 SubtractQuaternions(const FVector4& q1, const FVector4& q2);
};

inline Quaternion Quaternion::EulerToQuaternion(FVector Euler) {
    // 오일러 각도를 라디안으로 변환
    float cy = cosf(Euler.Z * 0.5f);   // cos(yaw / 2)
    float sy = sinf(Euler.Z * 0.5f);   // sin(yaw / 2)
    float cp = cosf(Euler.Y * 0.5f); // cos(pitch / 2)
    float sp = sinf(Euler.Y * 0.5f); // sin(pitch / 2)
    float cr = cosf(Euler.X * 0.5f);  // cos(roll / 2)
    float sr = sinf(Euler.X * 0.5f);  // sin(roll / 2)

    // 쿼터니언 계산
    Quaternion quaternion;
    quaternion.X = sr * cp * cy - cr * sp * sy; // X축
    quaternion.Y = cr * sp * cy + sr * cp * sy; // Y축
    quaternion.Z = cr * cp * sy - sr * sp * cy; // Z축
    quaternion.W = cr * cp * cy + sr * sp * sy; // W축 (스칼라)

    return quaternion;
}

inline FVector QuaternionToEuler(const FVector4& quaternion) {
    // 쿼터니언 요소 추출
    float X = quaternion.X;
    float Y = quaternion.Y;
    float Z = quaternion.Z;
    float W = quaternion.W;

    // 오일러 각도 계산
    FVector euler;

    // Pitch (x축 회전)
    float sinPitch = 2.0f * (W * X + Y * Z);
    float cosPitch = 1.0f - 2.0f * (X * X + Y * Y);
    euler.X = std::atan2(sinPitch, cosPitch);

    // Yaw (y축 회전)
    float sinYaw = 2.0f * (W * Y - Z * X);
    if (std::abs(sinYaw) >= 1.0f) {
        euler.Y = std::copysign(PIDIV2, sinYaw); // ±90도 (짐벌락 방지)
    } else {
        euler.Z = std::asin(sinYaw);
    }

    // Roll (z축 회전)
    float sinRoll = 2.0f * (W * Z + X * Y);
    float cosRoll = 1.0f - 2.0f * (Y * Y + Z * Z);
    euler.Z = std::atan2(sinRoll, cosRoll);

    return euler; // 반환: 라디안 단위의 오일러 각도
}

inline FVector4 AddQuaternions(const FVector4& q1, const FVector4& q2) {
    return FVector4(
        q1.X + q2.X,
        q1.Y + q2.Y,
        q1.Z + q2.Z,
        q1.W + q2.W
    );
}

inline FVector4 MultiplyQuaternions(const FVector4& q1, const FVector4& q2) {
    return FVector4(
        q1.W * q2.X + q1.X * q2.W + q1.Y * q2.Z - q1.Z * q2.Y, // X
        q1.W * q2.Y - q1.X * q2.Z + q1.Y * q2.W + q1.Z * q2.X, // Y
        q1.W * q2.Z + q1.X * q2.Y - q1.Y * q2.X + q1.Z * q2.W, // Z
        q1.W * q2.W - q1.X * q2.X - q1.Y * q2.Y - q1.Z * q2.Z  // W
    );
}

inline FVector4 SubtractQuaternions(const FVector4& q1, const FVector4& q2) {
    return FVector4(
        q1.X - q2.X,
        q1.Y - q2.Y,
        q1.Z - q2.Z,
        q1.W - q2.W
    );
}