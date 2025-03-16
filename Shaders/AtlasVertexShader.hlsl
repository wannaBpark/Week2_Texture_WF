struct VertexInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct HullInput
{
    float3 position : POSITION;
};

HullInput VS(VertexInput input)
{
    HullInput output;
    output.position = input.position;
    return output;
}