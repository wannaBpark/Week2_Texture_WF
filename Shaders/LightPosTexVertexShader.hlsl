
cbuffer constants : register(b0)
{
    matrix Model;
    matrix View;
    matrix Projection;
    matrix InvTranspose;
    float4 CustomColor;
    uint bUseVertexColor;
    float3 eyeWorldPos;
    float4 indexColor;
    uint bIsPicked;
    float3 Padding;
}

struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};
struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 color : COLOR; // Color to pass to the pixel shader
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
};

PS_INPUT mainVS(VS_INPUT input)
{
    // output.depthPosition = output.position;
    
    PS_INPUT output;
    float4 position;

    position = mul(float4(input.position, 1.0f), Model);
    position = mul(position, View);
    position = mul(position, Projection);
    output.position = position;
    
    output.normal = mul(float4(input.normal, 1.0f), InvTranspose);
    output.texcoord = input.texcoord;
    output.color = bUseVertexColor == 1 ? input.color : CustomColor;

    return output;
}