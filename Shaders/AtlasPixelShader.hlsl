Texture2D atlasTexture : register(t0);
SamplerState atlasSampler : register(s0);

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 localPosition : POSITION;
    float2 texcoord : TEXCOORD0; 
};

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.texcoord;
    return atlasTexture.Sample(atlasSampler, uv);
}	