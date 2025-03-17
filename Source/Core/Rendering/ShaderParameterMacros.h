#pragma once

#define BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(StructType) \
    class alignas(16) StructType \
    { \
    public:
#define SHADER_PARAMETER(Type, Name) \
    Type Name;

#define END_GLOBAL_SHADER_PARAMETER_STRUCT() \
    };

struct FPosColor
{
    float X, Y, Z;    // Position
    float R, G, B, A; // Color
};

struct FPosColorNormal
{
    float X, Y, Z;    // Position
    float R, G, B, A; // Color 
    float NX, NY, NZ; // Normal 
};

struct FPosNormalTex
{
    float X, Y, Z;    // Position
    float NX, NY, NZ; // Normal 
    float U, V;       // Texcoord
};

struct FPosColorNormalTex
{
    float X, Y, Z;    // Position
    float R, G, B, A; // Color
    float NX, NY, NZ; // Normal 
    float U, V;       // Texcoord
};

enum class InputLayoutType
{
    POSCOLOR,
    POSCOLORNORMAL,
    POSNORMALTEX,
    POSCOLORNORMALTEX,
};

// Constant Buffer 구조체 정의

BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FConstants)
    SHADER_PARAMETER(FMatrix, MVP)
    SHADER_PARAMETER(FVector4, Color)
    SHADER_PARAMETER(uint32, bUseVertexColor)
    SHADER_PARAMETER(FVector, eyeWorldPos)
    SHADER_PARAMETER(FVector4, indexColor)
    SHADER_PARAMETER(uint32, bIsPicked)
    SHADER_PARAMETER(FVector, Padding)
END_GLOBAL_SHADER_PARAMETER_STRUCT()

BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FPickingConstants)
    SHADER_PARAMETER(FVector4, UUIDColor)
END_GLOBAL_SHADER_PARAMETER_STRUCT()

BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FDepthConstants)
    SHADER_PARAMETER(unsigned int, DepthOffset)
    SHADER_PARAMETER(int, nearPlane)
    SHADER_PARAMETER(int, farPlane)
END_GLOBAL_SHADER_PARAMETER_STRUCT()

BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(ConstantUpdateInfo)
    SHADER_PARAMETER(const FMatrix&, WorldPosition)
    SHADER_PARAMETER(const FVector4&, Color)
    SHADER_PARAMETER(uint32, bUseVertexColor)
    SHADER_PARAMETER(FVector, eyeWorldPos)
    SHADER_PARAMETER(FVector4, indexColor)
 END_GLOBAL_SHADER_PARAMETER_STRUCT()

BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FAtlasConstants)
    SHADER_PARAMETER(FMatrix, WorldPosition)
    SHADER_PARAMETER(FVector4, AtlasSzOffset)
END_GLOBAL_SHADER_PARAMETER_STRUCT()
//struct alignas(16) FConstants
//{
//    FMatrix MVP;
//    FVector4 Color;
//    // true인 경우 Vertex Color를 사용하고, false인 경우 Color를 사용합니다.
//    uint32 bUseVertexColor;
//    FVector Padding;
//};
//
//struct alignas(16) FPickingConstants
//{
//    FVector4 UUIDColor;
//};
//
//struct alignas(16) FDepthConstants {
//    unsigned int DepthOffset;
//    int nearPlane;
//    int farPlane;
//};
//
//struct ConstantUpdateInfo
//{
//    const FTransform& Transform;
//    const FVector4& Color;
//    bool bUseVertexColor;
//};