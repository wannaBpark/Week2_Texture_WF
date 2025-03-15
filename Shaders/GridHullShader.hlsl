cbuffer constants : register(b0)
{
    matrix MVP;
    float4 CustomColor;
    uint bUseVertexColor;
    float3 eyeWorldPos;
    float4 indexColor;
}
struct HullInput
{
    float3 position : POSITION;
};

struct PatchTess
{
    float EdgeTess[4] : SV_TessFactor; // 각 변의 테셀레이션 수준
    float InsideTess[2] : SV_InsideTessFactor; // 내부 테셀레이션 수준
};

// 카메라 거리 기반 테셀레이션 계산
float ComputeTessellationFactor(float3 worldPos)
{
    float3 camPos = eyeWorldPos;
    float dist = distance(worldPos, camPos);

    float tessFactor = 1.0f;
    if (dist < 10.0f)
        tessFactor = 10.0f;
    else if (dist < 20.0f)
        tessFactor = 6.0f;
    else if (dist < 50.0f)
        tessFactor = 3.0f;
    else
        tessFactor = 1.0f;

    return tessFactor;
}

PatchTess HSConstant(InputPatch<HullInput, 4> patch, uint PatchID : SV_PrimitiveID)
{
    PatchTess output;
    
    float tessFactor = ComputeTessellationFactor(patch[0].position);

    // 테셀레이션 레벨 설정 (카메라 거리 기반)
    output.EdgeTess[0] = tessFactor;
    output.EdgeTess[1] = tessFactor;
    output.EdgeTess[2] = tessFactor;
    output.EdgeTess[3] = tessFactor;

    output.InsideTess[0] = tessFactor;
    output.InsideTess[1] = tessFactor;

    return output;
}

// Hull Shader 본체
[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[patchconstantfunc("HSConstant")]
[outputcontrolpoints(4)]
HullInput mainHS(InputPatch<HullInput, 4> patch, uint id : SV_OutputControlPointID)
{
    return patch[id];
}