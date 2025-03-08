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

	}

	return BufferInfo(Buffer, Size, Topology);
}

