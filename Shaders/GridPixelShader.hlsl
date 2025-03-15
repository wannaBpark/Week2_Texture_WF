struct DomainOutput
{
    float4 position : SV_POSITION;
};

float4 mainPS(DomainOutput input) : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f); // 흰색 그리드 라인
}