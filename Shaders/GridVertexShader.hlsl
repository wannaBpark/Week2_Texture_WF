struct VS_INPUT
{
    float3 position : POSITION;
    float4 color : COLOR;
};
struct HullInput
{
    float3 position : POSITION;
};

HullInput mainVS(VS_INPUT input)
{
    HullInput output;
    output.position = input.position;
    return output;
}