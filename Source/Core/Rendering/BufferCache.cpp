#include "BufferCache.h"
#include "Core/Engine.h"
#include "Primitive/PrimitiveVertices.h"
#include "Core/Rendering/ShaderParameterMacros.h"

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
	ComPtr<ID3D11Buffer> Buffer = nullptr;
	ComPtr<ID3D11Buffer> IndexBuffer = nullptr;
	int Size = 0;
	D3D_PRIMITIVE_TOPOLOGY Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	switch (Type)
	{
		using enum EPrimitiveType; // [C++ 20] 범위있는 열거형의 이름 없이 열거자를 유효범위내 사용
	case EPT_Line:
		Size = std::size(LineVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(LineVertices, sizeof(FVertexSimple) * Size);
		Topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case EPT_Triangle:
		Size = std::size(TriangleVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(TriangleVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPT_Cube:
		Size = std::size(CubeVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(CubeVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPT_Sphere:
		Size = std::size(SphereVertices);
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(SphereVertices, sizeof(FVertexSimple) * Size);
		break;
	case EPT_Cylinder:
	{
		TArray<FVertexSimple> Vertices = CreateCylinderVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}
	case EPT_Cone:
	{
		TArray<FVertexSimple> Vertices = CreateConeVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FVertexSimple) * Size);
		break;
	}
	case EPT_CubeTex:
		auto [Vertices, Indices]= CreateCubeTexVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FPosColorNormalTex) * Size);
		IndexBuffer = UEngine::Get().GetRenderer()->CreateIndexBuffer(Indices);
		Size = Indices.size();
		break;
	}

	// 현재 VertexBuffer는 map에 존재하지 않으므로
	UEngine::Get().GetRenderer()->VertexBufferMap.insert({ Type, Buffer });
	UEngine::Get().GetRenderer()->VertexCountMap.insert({ Type, Size });
	UEngine::Get().GetRenderer()->TopologyMap.insert({ Type, Topology });

	// IndexBuffer를 사용하는 Primitive Type인 경우
	if (IndexBuffer != nullptr) {
		UEngine::Get().GetRenderer()->IndexBufferMap.insert({ Type, IndexBuffer });
	}
	

	return BufferInfo(Buffer.Get(), Size, Topology);
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


std::tuple<TArray<FPosColorNormalTex>, std::vector<uint32> > FBufferCache::CreateCubeTexVertices()
{
	TArray<FPosColorNormalTex> Vertices;
	std::vector<uint32> Indices;
	
	//// Z- 앞면
	//Vertices.Add({ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });  // Bottom-left
	//Vertices.Add({ -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });   // Top-left (yellow)
	//Vertices.Add({ 0.5f,  0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });  // Top-right (blue))
	//Vertices.Add({ 0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });  // Bottom-right (green)
	//	// Back face (Z+)
	//Vertices.Add({ 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,0.0f, 0.0f});  // Bottom-left (cyan)
	//Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,1.0f, 0.0f});  // Top-left (blue)
	//Vertices.Add({ -0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f , 0.0f, 0.0f,-1.0f,1.0f, 1.0f});  // Top-right (yellow)
	//Vertices.Add({ -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f, 1.0f , 0.0f, 0.0f,-1.0f,0.0f, 1.0f});  // Bottom-right (magenta)

	//	// Left face (X-)
	//Vertices.Add({ -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 0.0f}); // Bottom-left (purple)
	//Vertices.Add({ -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 0.0f}); // Top-left (blue)
	//Vertices.Add({ -0.5f,  0.5f,  -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 1.0f}); // Top-right (yellow)
	//Vertices.Add({ -0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 1.0f}); // Bottom-right (green)

	//	// Right face (X+)
	//Vertices.Add({ 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f});  // Bottom-left (orange)
	//Vertices.Add({ 0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 0.0f});  // Top-left (purple)
	//Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f});  // Top-right (dark blue)
	//Vertices.Add({ 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f});  // Bottom-right (gray)
	//																  
	//	// Top face (Y+)											  
	//Vertices.Add({ -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f });  // Bottom-left (light green)
	//Vertices.Add({ -0.5f, 0.5f,  0.5f,  0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f});  // Top-left (cyan)
	//Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 1.0f , 0.0f, 1.0f, 0.0f,1.0f, 1.0f});  // Top-right (brown)
	//Vertices.Add({ 0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f , 0.0f, 1.0f, 0.0f,0.0f, 1.0f});  // Bottom-right (white)
	//																  
	//	// Bottom face (Y-)											  
	//Vertices.Add({ 0.5f,  -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,0.0f, 0.0f});  // Bottom-left (brown)
	//Vertices.Add({ 0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,1.0f, 0.0f});  // Top-left (red)
	//Vertices.Add({ -0.5f,  -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f , 0.0f, -1.0f,0.0f,1.0f, 1.0f});  // Top-right (green)
	//Vertices.Add({ -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f, 1.0f , 0.0f, -1.0f,0.0f,0.0f, 1.0f});  // Bottom-right (purple)

	// Z- 앞면
	Vertices.Add({ -0.5f,  -0.5f,-0.5f,  1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });  // Bottom-left
	Vertices.Add({ -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });   // Top-left (yellow)
	Vertices.Add({ -0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });  // Top-right (blue))
	Vertices.Add({ -0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });  // Bottom-right (green)
	// Back face (Z+)
	Vertices.Add({ 0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,0.0f, 0.0f });  // Bottom-left (cyan)
	Vertices.Add({ 0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,1.0f, 0.0f });  // Top-left (blue)
	Vertices.Add({ 0.5f,  0.5f,-0.5f,   1.0f, 1.0f, 0.0f, 1.0f , 0.0f, 0.0f,-1.0f,1.0f, 1.0f });  // Top-right (yellow)
	Vertices.Add({ 0.5f, -0.5f,-0.5f,   1.0f, 0.0f, 1.0f, 1.0f , 0.0f, 0.0f,-1.0f,0.0f, 1.0f });  // Bottom-right (magenta)

	// Left face (X-)
	Vertices.Add({ 0.5f,  -0.5f,-0.5f,   1.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 0.0f }); // Bottom-left (purple)
	Vertices.Add({ 0.5f,   0.5f,-0.5f,   0.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 0.0f }); // Top-left (blue)
	Vertices.Add({ -0.5f,  0.5f,-0.5f,    1.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 1.0f }); // Top-right (yellow)
	Vertices.Add({ -0.5f, -0.5f,-0.5f,    0.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 1.0f }); // Bottom-right (green)

	// Right face (X+)
	Vertices.Add({ -0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f });  // Bottom-left (orange)
	Vertices.Add({ -0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 0.0f });  // Top-left (purple)
	Vertices.Add({ 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f });  // Top-right (dark blue)
	Vertices.Add({ 0.5f,  -0.5f, 0.5f,    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f });  // Bottom-right (gray)
	Vertices.Add({ -0.5f,  0.5f,  -0.5f,  0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f });  // Bottom-left (light green)
	Vertices.Add({ 0.5f,   0.5f, -0.5f,   0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f });  // Top-left (cyan)
	Vertices.Add({ 0.5f,   0.5f, 0.5f,    0.5f, 0.5f, 0.0f, 1.0f , 0.0f, 1.0f, 0.0f,1.0f, 1.0f });  // Top-right (brown)
	Vertices.Add({ -0.5f,  0.5f,  0.5f,   0.5f, 1.0f, 1.0f, 1.0f , 0.0f, 1.0f, 0.0f,0.0f, 1.0f });  // Bottom-right (white)
	Vertices.Add({ -0.5f,  -0.5f, 0.5f,   0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,0.0f, 0.0f });  // Bottom-left (brown)
	Vertices.Add({ 0.5f,  -0.5f, 0.5f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,1.0f, 0.0f });  // Top-left (red)
	Vertices.Add({ 0.5f,  -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f , 0.0f, -1.0f,0.0f,1.0f, 1.0f });  // Top-right (green)
	Vertices.Add({ -0.5f,  -0.5f, -0.5f,  1.0f, 0.0f, 0.5f, 1.0f , 0.0f, -1.0f,0.0f,0.0f, 1.0f });  // Bottom-right (purple)

	Indices = {
		0,  1,  2,  0,  2,  3,  // 윗면
		4,  5,  6,  4,  6,  7,  // 아랫면
		8,  9,  10, 8,  10, 11, // 앞면
		12, 13, 14, 12, 14, 15, // 뒷면
		16, 17, 18, 16, 18, 19, // 왼쪽
		20, 21, 22, 20, 22, 23  // 오른쪽
	};

	return { Vertices, Indices };
}