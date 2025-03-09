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
		TArray<FVertexSimple> Vertices = CreateArrowVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}

	return BufferInfo(Buffer, Size, Topology);
}

TArray<FVertexSimple> FBufferCache::CreateArrowVertices()
{
	TArray<FVertexSimple> Vertices;

	// 원통
	for (float Angle = 0; Angle < 360; Angle += 10)
	{
		float Rad = FMath::DegreesToRadians(Angle);
		float X = cos(Rad) * 0.8f;
		float Y = sin(Rad) * 0.8f;

		Vertices.Add({ X, Y, 0, 1, 1, 1, 1 });
		Vertices.Add({ X, Y, 1, 1, 1, 1, 1 });
	}

	// 머리
	for (float angle = 0; angle < 360; angle += 10)
	{
		float Rad = FMath::DegreesToRadians(angle);
		float X = 0.2f * cos(Rad);
		float Y = 0.2f * sin(Rad);

		// 원뿔의 버텍스들 (길이 0.2로 설정)
		Vertices.Add({ X, Y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	}

	// 꼭지점
	Vertices.Add({ 0.0f, 0.0f, 1.2f, 1.0f, 1.0f, 1.0f, 1.0f });

	return Vertices;
}
