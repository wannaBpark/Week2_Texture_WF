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
	case EPrimitiveType::EPT_Arrow:
		TArray<FVertexSimple> Vertices = CreateCylinderVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}

	return BufferInfo(Buffer, Size, Topology);
}

TArray<FVertexSimple> FBufferCache::CreateArrowVertices()
{
	float cylinderRadius = 1.0f;
	float cylinderHeight = 2.0f;
	float coneRadius = 1.1f;  // 원통보다 살짝 큰 반지름
	float coneHeight = 1.0f;

	TArray<FVertexSimple> shapeVertices;

	// 원통의 바닥과 몸체 (원통은 세그먼트로 나눠서 구성 가능, 여기서는 간단히 두 점으로 표현)
	for (int i = 0; i < 360; i += 10) {
		float angle = FMath::DegreesToRadians(i);
		float x = cylinderRadius * cos(angle);
		float y = cylinderRadius * sin(angle);

		// 원통 바닥 (z=0)
		shapeVertices.Add({ x, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });  // 녹색 바닥

		// 원통 윗면 (z=cylinderHeight)
		shapeVertices.Add({ x, y, cylinderHeight, 0.0f, 1.0f, 0.0f, 1.0f });  // 초록색 윗면
	}

	// 원통의 세로 면 (높이를 따라 세그먼트를 나눠서 추가)
	for (int i = 0; i < 360; i += 10) {
		float angle = FMath::DegreesToRadians(i);
		float x = cylinderRadius * cos(angle);
		float y = cylinderRadius * sin(angle);

		// 원통의 세로 면
		shapeVertices.Add({ x, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });
		shapeVertices.Add({ x, y, cylinderHeight, 0.0f, 1.0f, 0.0f, 1.0f });
	}

	// 콘의 바닥 (콘의 반지름이 원통보다 살짝 커짐)
	for (int i = 0; i < 360; i += 10) {
		float angle = FMath::DegreesToRadians(i);
		float x = coneRadius * cos(angle);
		float y = coneRadius * sin(angle);

		// 콘 바닥 (z = cylinderHeight)
		shapeVertices.Add({ x, y, cylinderHeight, 1.0f, 0.0f, 0.0f, 1.0f });  // 빨간색
	}

	// 콘의 꼭대기 (z = cylinderHeight + coneHeight)
	shapeVertices.Add({ 0.0f, 0.0f, cylinderHeight + coneHeight, 1.0f, 0.0f, 0.0f, 1.0f });  // 빨간색 꼭대기

	// 콘의 삼각형 면을 추가 (꼭대기와 바닥을 연결하는 삼각형들)
	for (int i = 0; i < 360; i += 10) {
		float angle1 = FMath::DegreesToRadians(i);
		float angle2 = FMath::DegreesToRadians(i + 10);

		float x1 = coneRadius * cos(angle1);
		float y1 = coneRadius * sin(angle1);
		float x2 = coneRadius * cos(angle2);
		float y2 = coneRadius * sin(angle2);

		// 콘의 삼각형 면
		shapeVertices.Add({ x1, y1, cylinderHeight, 1.0f, 0.0f, 0.0f, 1.0f });  // 빨간색
		shapeVertices.Add({ x2, y2, cylinderHeight, 1.0f, 0.0f, 0.0f, 1.0f });  // 빨간색
		shapeVertices.Add({ 0.0f, 0.0f, cylinderHeight + coneHeight, 1.0f, 0.0f, 0.0f, 1.0f });  // 빨간색 꼭대기
	}

	return shapeVertices;
}

TArray<FVertexSimple> FBufferCache::CreateConeVertices()
{
	TArray<FVertexSimple> vertices;

	int segments = 36;
	float radius = 1.f;
	float height = 2.f;


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
	float radius = 1.f;
	float height = 2.f;


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
		vertices.Add({ x1, y1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });
		vertices.Add({ x2, y2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f });

		// 윗면 삼각형
		vertices.Add({ 0.0f, 0.0f, height, 0.0f, 1.0f, 0.0f, 1.0f });
		vertices.Add({ x2, y2, height, 0.0f, 1.0f, 0.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 1.0f, 0.0f, 1.0f });

		// 옆면 삼각형 두 개
		vertices.Add({ x1, y1, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x2, y2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });

		vertices.Add({ x2, y2, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x1, y1, height, 0.0f, 0.0f, 1.0f, 1.0f });
		vertices.Add({ x2, y2, height, 0.0f, 0.0f, 1.0f, 1.0f });
	}

	return vertices;
}
