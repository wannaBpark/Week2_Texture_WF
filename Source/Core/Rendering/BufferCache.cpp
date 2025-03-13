#include "BufferCache.h"
#include "Core/Engine.h"
#include "Primitive/PrimitiveVertices.h"

FBufferCache::FBufferCache()
{
}

FBufferCache::~FBufferCache()
{
}

void FBufferCache::Init()
{

}

BufferInfo FBufferCache::GetBufferInfo(EPrimitiveType Type)
{
	if (!Cache.contains(Type))
	{
		//여기서 버텍스 버퍼 생성한다
		auto bufferInfo = CreateVertexBufferInfo(Type);
		Cache.insert({ Type, bufferInfo });
	}

	return Cache[Type];
}

BufferInfo FBufferCache::CreateVertexBufferInfo(EPrimitiveType Type)
{
	ID3D11Buffer* Buffer = nullptr;
	int Size = 0;
	D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	switch (Type)
	{
	case EPrimitiveType::EPT_Line:
		Size = std::size(LineVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(LineVertices, sizeof(FVertexSimple) * Size);
		Topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case EPrimitiveType::EPT_Triangle:
		Size = std::size(TriangleVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(TriangleVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPrimitiveType::EPT_Cube:
		Size = std::size(CubeVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(CubeVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPrimitiveType::EPT_Sphere:
		Size = std::size(SphereVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(SphereVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPrimitiveType::EPT_Cylinder:
	{
		TArray<FVertexSimple> Vertices = CreateCylinderVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}
	case EPrimitiveType::EPT_Cone:
	{
		TArray<FVertexSimple> Vertices = CreateConeVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}
	case EPrimitiveType::EPT_Circle:
	{
		TArray<FVertexSimple> Vertices = CreateCircleVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}
	}

	return BufferInfo(Buffer, Size, Topology);
}


TArray<FVertexSimple> FBufferCache::CreateConeVertices()
{
	TArray<FVertexSimple> vertices;

	int segments = 36;
	float radius = 1.f;
	float height = 1.f;


	// 원뿔의 바닥
	for (int i = 0; i < segments; ++i)
	{
		float angle = 2.0f * PI * i / segments;
		float nextAngle = 2.0f * PI * (i + 1) / segments;

		float x1 = radius * cos(angle);
		float y1 = radius * sin(angle);
		float x2 = radius * cos(nextAngle);
		float y2 = radius * sin(nextAngle);

		 // 바닥 삼각형 (반시계 방향으로 추가)
        vertices.Add({ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });
        vertices.Add({ x2, y2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });
        vertices.Add({ x1, y1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });

        // 옆면 삼각형 (시계 방향으로 추가)
        vertices.Add({ x1, y1, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
        vertices.Add({ x2, y2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
        vertices.Add({ 0.0f, 0.0f, height, 0.0f, 1.0f, 0.0f, 1.0f });
	}

	return vertices;
}

TArray<FVertexSimple> FBufferCache::CreateCylinderVertices()
{
	TArray<FVertexSimple> vertices;
	
	int segments = 36;
	float radius = .03f;
	float height = .5f;


	// 원기둥의 바닥과 윗면
	for (int i = 0; i < segments; ++i)
	{
		float angle = 2.0f * PI * i / segments;
		float nextAngle = 2.0f * PI * (i + 1) / segments;

		float x1 = radius * cos(angle);
		float y1 = radius * sin(angle);
		float x2 = radius * cos(nextAngle);
		float y2 = radius * sin(nextAngle);

		// 바닥 삼각형
		vertices.Add({ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });
		vertices.Add({ x2, y2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });
		vertices.Add({ x1, y1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });

		// 윗면 삼각형
		vertices.Add({ 0.0f, 0.0f, height, 0.0f, 1.0f, 0.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 1.0f, 0.0f, 1.0f });
		vertices.Add({ x2, y2, height, 0.0f, 1.0f, 0.0f, 1.0f });

		// 옆면 삼각형 두 개
		vertices.Add({ x1, y1, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x2, y2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 0.0f, 1.0f, 1.0f });

		vertices.Add({ x2, y2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x2, y2, height, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 0.0f, 1.0f, 1.0f });
	}

	return vertices;
}

TArray<FVertexSimple> FBufferCache::CreateCircleVertices()
{
    TArray<FVertexSimple> vertices;

    int DISC_RESOLUTION = 128; // 원을 구성하는 정점 개수
    float outerRadius = 1.0f;  // 외곽 반지름
    float innerRadius = 0.9f;  // 내부 반지름
    float height = 0.1f;       // 원기둥의 두께
    float angleStep = 2.0f * PI / DISC_RESOLUTION;

    // 위쪽 원 (Top) - CCW (반시계 방향)
    for (int i = 0; i < DISC_RESOLUTION; ++i)
    {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        float x0 = cos(angle);
        float z0 = sin(angle);
        float x1 = cos(nextAngle);
        float z1 = sin(nextAngle);

        // 삼각형 1 (탑면)
        vertices.Add({ x0 * outerRadius, height / 2, z0 * outerRadius, 1, 1, 1, 1 });
        vertices.Add({ x0 * innerRadius, height / 2, z0 * innerRadius, 1, 1, 1, 1 });
        vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1 });

        // 삼각형 2 (탑면)
        vertices.Add({ x0 * innerRadius, height / 2, z0 * innerRadius, 1, 1, 1, 1 });
        vertices.Add({ x1 * innerRadius, height / 2, z1 * innerRadius, 1, 1, 1, 1 });
        vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1 });
    }

    // 바닥면 (Bottom) - CW (시계 방향)
    for (int i = 0; i < DISC_RESOLUTION; ++i)
    {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        float x0 = cos(angle);
        float z0 = sin(angle);
        float x1 = cos(nextAngle);
        float z1 = sin(nextAngle);

        // 삼각형 1 (바닥면)
        vertices.Add({ x1 * outerRadius, -height / 2, z1 * outerRadius, 1, 1, 1, 1 });
        vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1 });
        vertices.Add({ x0 * outerRadius, -height / 2, z0 * outerRadius, 1, 1, 1, 1 });

        // 삼각형 2 (바닥면)
        vertices.Add({ x1 * outerRadius, -height / 2, z1 * outerRadius, 1, 1, 1, 1 });
        vertices.Add({ x1 * innerRadius, -height / 2, z1 * innerRadius, 1, 1, 1, 1 });
        vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1 });
    }

    // 측면 벽 추가 (외곽) - 시계 방향 (CW)
    for (int i = 0; i < DISC_RESOLUTION; ++i)
    {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        float x0 = cos(angle);
        float z0 = sin(angle);
        float x1 = cos(nextAngle);
        float z1 = sin(nextAngle);

        // 삼각형 1 (외곽 벽면)
        vertices.Add({ x0 * outerRadius, height / 2, z0 * outerRadius, 1, 1, 1, 1 });
        
        vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1 });
		vertices.Add({ x0 * outerRadius, -height / 2, z0 * outerRadius, 1, 1, 1, 1 });

        // 삼각형 2 (외곽 벽면)
        vertices.Add({ x0 * outerRadius, -height / 2, z0 * outerRadius, 1, 1, 1, 1 });
        
        vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1 });
		vertices.Add({ x1 * outerRadius, -height / 2, z1 * outerRadius, 1, 1, 1, 1 });
    }

    // 측면 벽 추가 (내부) - 반시계 방향 (CCW)
    for (int i = 0; i < DISC_RESOLUTION; ++i)
    {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        float x0 = cos(angle);
        float z0 = sin(angle);
        float x1 = cos(nextAngle);
        float z1 = sin(nextAngle);

        // 삼각형 1 (내부 벽면)
        vertices.Add({ x0 * innerRadius, height / 2, z0 * innerRadius, 1, 1, 1, 1 });
        
        vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1 });
		vertices.Add({ x1 * innerRadius, height / 2, z1 * innerRadius, 1, 1, 1, 1 });

        // 삼각형 2 (내부 벽면)
        vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1 });
        
        vertices.Add({ x1 * innerRadius, -height / 2, z1 * innerRadius, 1, 1, 1, 1 });
		vertices.Add({ x1 * innerRadius, height / 2, z1 * innerRadius, 1, 1, 1, 1 });
    }

    return vertices;
}


