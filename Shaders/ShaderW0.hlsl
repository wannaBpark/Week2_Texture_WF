// ShaderW0.hlsl
cbuffer constants : register(b0)
{
    matrix MVP;
    float4 CustomColor;
    uint bUseVertexColor;
}

cbuffer UUIDColor : register(b1){
    float4 UUIDColor;
}

struct VS_INPUT
{
    float4 position : POSITION; // Input position from vertex buffer
    float4 color : COLOR;       // Input color from vertex buffer
};

struct PS_INPUT
{
    float4 position : SV_POSITION; // Transformed position to pass to the pixel shader
    float4 color : COLOR;          // Color to pass to the pixel shader
};

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;

    output.position = mul(input.position, MVP);

    output.color = bUseVertexColor == 1 ? input.color : CustomColor;
    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    // Output the color directly
    return input.color;
}

float4 outlinePS(PS_INPUT input) : SV_TARGET
{
    // Output the color directly
    return float4(1.0f, 0.647f, 0.0f, 0.1f);
}

float4 PickingPS(PS_INPUT input):SV_TARGET{
    
    return UUIDColor;
}