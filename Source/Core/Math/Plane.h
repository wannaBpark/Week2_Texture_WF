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
	float roll = FMath::DegreesToRadians(Euler.X);
	float pitch = FMath::DegreesToRadians(Euler.Y);
	float yaw = FMath::DegreesToRadians(Euler.Z);

    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);

    FQuat q;
    q.W = cr * cp * cy + sr * sp * sy;
    q.X = sr * cp * cy - cr * sp * sy;
    q.Y = cr * sp * cy + sr * cp * sy;
    q.Z = cr * cp * sy - sr * sp * cy;

    return q;
}

inline FVector FQuat::QuaternionToEuler(const FQuat& Quat) {
    FVector angles;

    // roll (x-axis rotation)
    double sinr_cosp = 2 * (Quat.W * Quat.X + Quat.Y * Quat.Z);
    double cosr_cosp = 1 - 2 * (Quat.X * Quat.X + Quat.Y * Quat.Y);
    angles.X = std::atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = std::sqrt(1 + 2 * (Quat.W * Quat.Y - Quat.X * Quat.Z));
    double cosp = std::sqrt(1 - 2 * (Quat.W * Quat.Y - Quat.X * Quat.Z));
    angles.Y = 2 * std::atan2(sinp, cosp) - PI / 2;

    // yaw (z-axis rotation)
    double siny_cosp = 2 * (Quat.W * Quat.Z + Quat.X * Quat.Y);
    double cosy_cosp = 1 - 2 * (Quat.Y * Quat.Y + Quat.Z * Quat.Z);
    angles.Z = std::atan2(siny_cosp, cosy_cosp);

	angles.X = FMath::RadiansToDegrees(angles.X);
	angles.Y = FMath::RadiansToDegrees(angles.Y);
	angles.Z = FMath::RadiansToDegrees(angles.Z);

    return angles;
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