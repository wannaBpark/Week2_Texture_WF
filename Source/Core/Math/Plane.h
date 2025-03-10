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

struct alignas(16) FQuat : public FVector4{
    using FVector::X;
    using FVector::Y;
    using FVector::Z;
    using FVector4::W;

    FQuat() : FVector4(0.0f, 0.0f, 0.0f, 1.0f) {}
	explicit FQuat(float InX, float InY, float InZ, float InW) : FVector4(InX, InY, InZ, InW) {}
    explicit FQuat(FVector Rotation) : FVector4(EulerToQuaternion(Rotation)) {}
    FQuat(const FVector& Axis, float AngleInDegrees) : FVector4(AxisAngleToQuaternion(Axis, AngleInDegrees)) {}


    static FQuat EulerToQuaternion(FVector Euler);
    static FVector QuaternionToEuler(const FQuat& quaternion);
    static FQuat AxisAngleToQuaternion(const FVector& Axis, float AngleInDegrees);

    static FQuat AddQuaternions(const FQuat& q1, const FQuat& q2);
    static FQuat MultiplyQuaternions(const FQuat& q1, const FQuat& q2);
    static FQuat SubtractQuaternions(const FQuat& q1, const FQuat& q2);

	FVector GetEuler() const { return QuaternionToEuler(*this); }
};
inline FQuat FQuat::AxisAngleToQuaternion(const FVector& Axis, float AngleInDegrees) {
    float AngleInRadians = FMath::DegreesToRadians(AngleInDegrees);
    float HalfAngle = AngleInRadians * 0.5f;
    float s = sinf(HalfAngle);
    return FQuat(
        Axis.X * s,
        Axis.Y * s,
        Axis.Z * s,
        cosf(HalfAngle)
    );
}

inline FQuat FQuat::EulerToQuaternion(FVector Euler) 
{


    // 오일러 각도를 라디안으로 변환
    float cy = cosf(Euler.Z * 0.5f);   // cos(yaw / 2)
    float sy = sinf(Euler.Z * 0.5f);   // sin(yaw / 2)
    float cp = cosf(Euler.Y * 0.5f); // cos(pitch / 2)
    float sp = sinf(Euler.Y * 0.5f); // sin(pitch / 2)
    float cr = cosf(Euler.X * 0.5f);  // cos(roll / 2)
    float sr = sinf(Euler.X * 0.5f);  // sin(roll / 2)

    // 쿼터니언 계산
    FQuat quaternion;
    quaternion.X = sr * cp * cy - cr * sp * sy; // X축
    quaternion.Y = cr * sp * cy + sr * cp * sy; // Y축
    quaternion.Z = cr * cp * sy - sr * sp * cy; // Z축
    quaternion.W = cr * cp * cy + sr * sp * sy; // W축 (스칼라)

    return quaternion;
}

inline FVector FQuat::QuaternionToEuler(const FQuat& quaternion) {
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
    euler.X = FMath::RadiansToDegrees(std::atan2(sinPitch, cosPitch));

    // Yaw (y축 회전)
    float sinYaw = 2.0f * (W * Y - Z * X);
    if (std::abs(sinYaw) >= 1.0f) {
        euler.Y = FMath::RadiansToDegrees(std::copysign(PIDIV2, sinYaw)); // ±90도 (짐벌락 방지)
    } else {
        euler.Z = FMath::RadiansToDegrees(std::asin(sinYaw));
    }

    // Roll (z축 회전)
    float sinRoll = 2.0f * (W * Z + X * Y);
    float cosRoll = 1.0f - 2.0f * (Y * Y + Z * Z);
    euler.Z = FMath::RadiansToDegrees(std::atan2(sinRoll, cosRoll));

    return euler; // 반환: 라디안 단위의 오일러 각도
}

inline FQuat FQuat::AddQuaternions(const FQuat& q1, const FQuat& q2) {
    return FQuat(
        q1.X + q2.X,
        q1.Y + q2.Y,
        q1.Z + q2.Z,
        q1.W + q2.W
    );
}

inline FQuat FQuat::MultiplyQuaternions(const FQuat& q1, const FQuat& q2) {
    return FQuat(
        q1.W * q2.X + q1.X * q2.W + q1.Y * q2.Z - q1.Z * q2.Y, // X
        q1.W * q2.Y - q1.X * q2.Z + q1.Y * q2.W + q1.Z * q2.X, // Y
        q1.W * q2.Z + q1.X * q2.Y - q1.Y * q2.X + q1.Z * q2.W, // Z
        q1.W * q2.W - q1.X * q2.X - q1.Y * q2.Y - q1.Z * q2.Z  // W
    );
}

inline FQuat FQuat::SubtractQuaternions(const FQuat& q1, const FQuat& q2) {
    return FQuat(
        q1.X - q2.X,
        q1.Y - q2.Y,
        q1.Z - q2.Z,
        q1.W - q2.W
    );
}