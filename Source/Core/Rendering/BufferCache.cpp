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
	{
	auto [Vertices, Indices] = CreateCubeTexVertices();
	Size = Vertices.Num();
	Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FPosColorNormalTex) * Size);
	IndexBuffer = UEngine::Get().GetRenderer()->CreateIndexBuffer(Indices);
	Size = Indices.size();
	break;
	}
	case EPT_CylinderTex:
	{
		auto [Vertices, Indices] = CreateCylinderTexVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FPosColorNormalTex) * Size);
		IndexBuffer = UEngine::Get().GetRenderer()->CreateIndexBuffer(Indices);
		Size = Indices.size();
		break;
	}
	case EPT_TriangleTex:
	{
		auto [Vertices, Indices] = CreateTriangleTexVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FPosColorNormalTex) * Size);
		IndexBuffer = UEngine::Get().GetRenderer()->CreateIndexBuffer(Indices);
		Size = Indices.size();
		break;
	}
	case EPT_CircleTex:
	{
		auto [Vertices, Indices] = CreateCircleTexVertices();
		Size = Vertices.Num();
		Buffer = UEngine::Get().GetRenderer()->CreateVertexBuffer(Vertices.GetData(), sizeof(FPosColorNormalTex) * Size);
		IndexBuffer = UEngine::Get().GetRenderer()->CreateIndexBuffer(Indices);
		Size = Indices.size();
		break;
	}
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
	
	// Z- 앞면
	Vertices.Add({ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });  // Bottom-left
	Vertices.Add({ -0.5f, 0.5f,  -0.5f, 1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });   // Top-left (yellow)
	Vertices.Add({ 0.5f,  0.5f,  -0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });  // Top-right (blue))
	Vertices.Add({ 0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });  // Bottom-right (green)
		// Back face (Z+)
	Vertices.Add({ 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,0.0f, 0.0f});  // Bottom-left (cyan)
	Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,1.0f, 0.0f});  // Top-left (blue)
	Vertices.Add({ -0.5f,  0.5f, 0.5f,  1.0f, 1.0f, 0.0f, 1.0f , 0.0f, 0.0f,-1.0f,1.0f, 1.0f});  // Top-right (yellow)
	Vertices.Add({ -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 1.0f, 1.0f , 0.0f, 0.0f,-1.0f,0.0f, 1.0f});  // Bottom-right (magenta)

		// Left face (X-)
	Vertices.Add({ -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 0.0f}); // Bottom-left (purple)
	Vertices.Add({ -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 0.0f}); // Top-left (blue)
	Vertices.Add({ -0.5f,  0.5f,  -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 1.0f}); // Top-right (yellow)
	Vertices.Add({ -0.5f, -0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 1.0f}); // Bottom-right (green)

		// Right face (X+)
	Vertices.Add({ 0.5f, -0.5f, -0.5f,  1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f});  // Bottom-left (orange)
	Vertices.Add({ 0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 0.0f});  // Top-left (purple)
	Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f});  // Top-right (dark blue)
	Vertices.Add({ 0.5f, -0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f});  // Bottom-right (gray)
																	  
		// Top face (Y+)											  
	Vertices.Add({ -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f });  // Bottom-left (light green)
	Vertices.Add({ -0.5f, 0.5f,  0.5f,  0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f});  // Top-left (cyan)
	Vertices.Add({ 0.5f,  0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 1.0f , 0.0f, 1.0f, 0.0f,1.0f, 1.0f});  // Top-right (brown)
	Vertices.Add({ 0.5f,  0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f , 0.0f, 1.0f, 0.0f,0.0f, 1.0f});  // Bottom-right (white)
																	  
		// Bottom face (Y-)											  
	Vertices.Add({ 0.5f,  -0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,0.0f, 0.0f});  // Bottom-left (brown)
	Vertices.Add({ 0.5f,  -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,1.0f, 0.0f});  // Top-left (red)
	Vertices.Add({ -0.5f,  -0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f , 0.0f, -1.0f,0.0f,1.0f, 1.0f});  // Top-right (green)
	Vertices.Add({ -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.5f, 1.0f , 0.0f, -1.0f,0.0f,0.0f, 1.0f});  // Bottom-right (purple)

	//// Z- 앞면
	//Vertices.Add({ -0.5f,  -0.5f,-0.5f,  1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 0.0f, 0.0f });  // Bottom-left
	//Vertices.Add({ -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f , 0.0f, 0.0f, 1.0f, 1.0f, 0.0f });   // Top-left (yellow)
	//Vertices.Add({ -0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });  // Top-right (blue))
	//Vertices.Add({ -0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f });  // Bottom-right (green)
	//// Back face (Z+)
	//Vertices.Add({ 0.5f, -0.5f, 0.5f,    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,0.0f, 0.0f });  // Bottom-left (cyan)
	//Vertices.Add({ 0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,-1.0f,1.0f, 0.0f });  // Top-left (blue)
	//Vertices.Add({ 0.5f,  0.5f,-0.5f,   1.0f, 1.0f, 0.0f, 1.0f , 0.0f, 0.0f,-1.0f,1.0f, 1.0f });  // Top-right (yellow)
	//Vertices.Add({ 0.5f, -0.5f,-0.5f,   1.0f, 0.0f, 1.0f, 1.0f , 0.0f, 0.0f,-1.0f,0.0f, 1.0f });  // Bottom-right (magenta)

	//// Left face (X-)
	//Vertices.Add({ 0.5f,  -0.5f,-0.5f,   1.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 0.0f }); // Bottom-left (purple)
	//Vertices.Add({ 0.5f,   0.5f,-0.5f,   0.0f, 0.0f, 1.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 0.0f }); // Top-left (blue)
	//Vertices.Add({ -0.5f,  0.5f,-0.5f,    1.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,1.0f, 1.0f }); // Top-right (yellow)
	//Vertices.Add({ -0.5f, -0.5f,-0.5f,    0.0f, 1.0f, 0.0f, 1.0f, -1.0f,0.0f, 0.0f,0.0f, 1.0f }); // Bottom-right (green)

	//// Right face (X+)
	//Vertices.Add({ -0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 0.0f });  // Bottom-left (orange)
	//Vertices.Add({ -0.5f,  0.5f,  0.5f,   0.5f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 0.0f });  // Top-left (purple)
	//Vertices.Add({ 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,1.0f, 1.0f });  // Top-right (dark blue)
	//Vertices.Add({ 0.5f,  -0.5f, 0.5f,    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f });  // Bottom-right (gray)
	//Vertices.Add({ -0.5f,  0.5f,  -0.5f,  0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f });  // Bottom-left (light green)
	//Vertices.Add({ 0.5f,   0.5f, -0.5f,   0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,1.0f, 0.0f });  // Top-left (cyan)
	//Vertices.Add({ 0.5f,   0.5f, 0.5f,    0.5f, 0.5f, 0.0f, 1.0f , 0.0f, 1.0f, 0.0f,1.0f, 1.0f });  // Top-right (brown)
	//Vertices.Add({ -0.5f,  0.5f,  0.5f,   0.5f, 1.0f, 1.0f, 1.0f , 0.0f, 1.0f, 0.0f,0.0f, 1.0f });  // Bottom-right (white)
	//Vertices.Add({ -0.5f,  -0.5f, 0.5f,   0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,0.0f, 0.0f });  // Bottom-left (brown)
	//Vertices.Add({ 0.5f,  -0.5f, 0.5f,   1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f,0.0f,1.0f, 0.0f });  // Top-left (red)
	//Vertices.Add({ 0.5f,  -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f , 0.0f, -1.0f,0.0f,1.0f, 1.0f });  // Top-right (green)
	//Vertices.Add({ -0.5f,  -0.5f, -0.5f,  1.0f, 0.0f, 0.5f, 1.0f , 0.0f, -1.0f,0.0f,0.0f, 1.0f });  // Bottom-right (purple)

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

std::tuple<TArray<FPosColorNormalTex>, std::vector<uint32>> FBufferCache::CreateCylinderTexVertices()
{
	TArray<FPosColorNormalTex> Vertices;
	std::vector<uint32> Indices;

	int segments = 36;
	float radius = 0.03f;
	float height = 0.5f;

	// Bottom and top center points
	uint32 bottomCenterIndex = Vertices.Num();
	Vertices.Add({ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f });
	uint32 topCenterIndex = Vertices.Num();
	Vertices.Add({ 0.0f, 0.0f, height, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f });

	for (int i = 0; i < segments; ++i)
	{
		float angle = 2.0f * PI * i / segments;
		float nextAngle = 2.0f * PI * (i + 1) / segments;

		float x1 = radius * cos(angle);
		float y1 = radius * sin(angle);
		float x2 = radius * cos(nextAngle);
		float y2 = radius * sin(nextAngle);
		float u1 = static_cast<float>(i) / segments;
		float u2 = static_cast<float>(i + 1) / segments;

		float nx1 = cos(angle);
		float ny1 = sin(angle);
		float nx2 = cos(nextAngle);
		float ny2 = sin(nextAngle);

		// Bottom face
		uint32 v1 = Vertices.Num();
		Vertices.Add({ x1, y1, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, x1 * 0.5f + 0.5f, y1 * 0.5f + 0.5f });
		uint32 v2 = Vertices.Num();
		Vertices.Add({ x2, y2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, x2 * 0.5f + 0.5f, y2 * 0.5f + 0.5f });
		Indices.insert(Indices.end(), { bottomCenterIndex, v2, v1 });

		// Top face
		uint32 v3 = Vertices.Num();
		Vertices.Add({ x1, y1, height, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, x1 * 0.5f + 0.5f, y1 * 0.5f + 0.5f });
		uint32 v4 = Vertices.Num();
		Vertices.Add({ x2, y2, height, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, x2 * 0.5f + 0.5f, y2 * 0.5f + 0.5f });
		Indices.insert(Indices.end(), { topCenterIndex, v3, v4 });

		// Side faces with duplicated vertices for correct normals and UV mapping
		uint32 v5 = Vertices.Num();
		Vertices.Add({ x1, y1, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, nx1, ny1, 0.0f, u1, 0.0f });
		uint32 v6 = Vertices.Num();
		Vertices.Add({ x1, y1, height, 0.0f, 1.0f, 0.0f, 1.0f, nx1, ny1, 0.0f, u1, 1.0f });
		uint32 v7 = Vertices.Num();
		Vertices.Add({ x2, y2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, nx2, ny2, 0.0f, u2, 0.0f });
		uint32 v8 = Vertices.Num();
		Vertices.Add({ x2, y2, height, 0.0f, 1.0f, 0.0f, 1.0f, nx2, ny2, 0.0f, u2, 1.0f });

		Indices.insert(Indices.end(), { v5, v7, v6 });
		Indices.insert(Indices.end(), { v7, v8, v6 });
	}

	return { Vertices, Indices };
}

std::tuple<TArray<FPosColorNormalTex>, std::vector<uint32>> FBufferCache::CreateTriangleTexVertices()
{
	TArray<FPosColorNormalTex> Vertices;
	std::vector<uint32> Indices;

	float size = 0.5f; // 한 변의 길이
	float height = sqrt(3.0f) / 2.0f * size; // 정삼각형 높이

	// vertex
	FVector v0 = { 0.0f,  height / 2.0f, 0.0f };
	FVector v1 = { -size / 2.0f, -height / 2.0f, 0.0f };
	FVector v2 = { size / 2.0f, -height / 2.0f, 0.0f };

	// front_normal - z+
	FVector normalFront = { 0.0f, 0.0f, 1.0f };

	// backfront_normal - z-
	FVector normalBack = { 0.0f, 0.0f, -1.0f };

	// front_face
	uint32 i0 = Vertices.Num();
	Vertices.Add({ v0.X, v0.Y, v0.Z, 1.0f, 0.0f, 0.0f, 1.0f, normalFront.X, normalFront.Y, normalFront.Z, 0.5f, 1.0f });
	uint32 i1 = Vertices.Num();
	Vertices.Add({ v1.X, v1.Y, v1.Z, 0.0f, 1.0f, 0.0f, 1.0f, normalFront.X, normalFront.Y, normalFront.Z, 0.0f, 0.0f });
	uint32 i2 = Vertices.Num();
	Vertices.Add({ v2.X, v2.Y, v2.Z, 0.0f, 0.0f, 1.0f, 1.0f, normalFront.X, normalFront.Y, normalFront.Z, 1.0f, 0.0f });

	// 
	Indices.insert(Indices.end(), { i0, i1, i2 });

	//back_face
	uint32 i3 = Vertices.Num();
	Vertices.Add({ v0.X, v0.Y, v0.Z, 1.0f, 0.0f, 0.0f, 1.0f, normalBack.X, normalBack.Y, normalBack.Z, 0.5f, 1.0f });
	uint32 i4 = Vertices.Num();
	Vertices.Add({ v2.X, v2.Y, v2.Z, 0.0f, 0.0f, 1.0f, 1.0f, normalBack.X, normalBack.Y, normalBack.Z, 1.0f, 0.0f });
	uint32 i5 = Vertices.Num();
	Vertices.Add({ v1.X, v1.Y, v1.Z, 0.0f, 1.0f, 0.0f, 1.0f, normalBack.X, normalBack.Y, normalBack.Z, 0.0f, 0.0f });


	Indices.insert(Indices.end(), { i3, i4, i5 });

	return { Vertices, Indices };
}

std::tuple<TArray<FPosColorNormalTex>, std::vector<uint32>> FBufferCache::CreateCircleTexVertices()
{
	TArray<FPosColorNormalTex> Vertices;
	std::vector<uint32> Indices;

	int DISC_RESOLUTION = 128; // 원을 구성하는 정점 개수
	float outerRadius = 1.0f;  // 외곽 반지름
	float innerRadius = 0.9f;  // 내부 반지름
	float height = 0.1f;       // 원기둥의 두께
	float angleStep = 2.0f * PI / DISC_RESOLUTION;

	uint32 topCenterIndex = Vertices.Num();
	Vertices.Add({ 0.0f, height / 2, 0.0f, 1, 1, 1, 1, 0, 1, 0, 0.5f, 0.5f });
	uint32 bottomCenterIndex = Vertices.Num();
	Vertices.Add({ 0.0f, -height / 2, 0.0f, 1, 1, 1, 1, 0, -1, 0, 0.5f, 0.5f });

	for (int i = 0; i < DISC_RESOLUTION; ++i)
	{
		float angle = i * angleStep;
		float nextAngle = (i + 1) * angleStep;

		float x0 = cos(angle);
		float z0 = sin(angle);
		float x1 = cos(nextAngle);
		float z1 = sin(nextAngle);

		float u0 = x0 * 0.5f + 0.5f;
		float v0 = z0 * 0.5f + 0.5f;
		float u1 = x1 * 0.5f + 0.5f;
		float v1 = z1 * 0.5f + 0.5f;

		// 위쪽 원면 (탑)
		uint32 v1_t = Vertices.Num();
		Vertices.Add({ x0 * outerRadius, height / 2, z0 * outerRadius, 1, 1, 1, 1, 0, 1, 0, u0, v0 });
		uint32 v2_t = Vertices.Num();
		Vertices.Add({ x0 * innerRadius, height / 2, z0 * innerRadius, 1, 1, 1, 1, 0, 1, 0, u0, v0 });
		uint32 v3_t = Vertices.Num();
		Vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1, 0, 1, 0, u1, v1 });
		uint32 v4_t = Vertices.Num();
		Vertices.Add({ x1 * innerRadius, height / 2, z1 * innerRadius, 1, 1, 1, 1, 0, 1, 0, u1, v1 });

		Indices.insert(Indices.end(), { v1_t, v2_t, v3_t, v2_t, v4_t, v3_t });

		// 바닥면 (Bottom)
		uint32 v1_b = Vertices.Num();
		Vertices.Add({ x0 * outerRadius, -height / 2, z0 * outerRadius, 1, 1, 1, 1, 0, -1, 0, u0, v0 });
		uint32 v2_b = Vertices.Num();
		Vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1, 0, -1, 0, u0, v0 });
		uint32 v3_b = Vertices.Num();
		Vertices.Add({ x1 * outerRadius, -height / 2, z1 * outerRadius, 1, 1, 1, 1, 0, -1, 0, u1, v1 });
		uint32 v4_b = Vertices.Num();
		Vertices.Add({ x1 * innerRadius, -height / 2, z1 * innerRadius, 1, 1, 1, 1, 0, -1, 0, u1, v1 });

		Indices.insert(Indices.end(), { v3_b, v2_b, v1_b, v3_b, v4_b, v2_b });

		// 외곽 측면
		uint32 v1_s = Vertices.Num();
		Vertices.Add({ x0 * outerRadius, height / 2, z0 * outerRadius, 1, 1, 1, 1, x0, 0, z0, u0, 1.0f });
		uint32 v2_s = Vertices.Num();
		Vertices.Add({ x1 * outerRadius, height / 2, z1 * outerRadius, 1, 1, 1, 1, x1, 0, z1, u1, 1.0f });
		uint32 v3_s = Vertices.Num();
		Vertices.Add({ x0 * outerRadius, -height / 2, z0 * outerRadius, 1, 1, 1, 1, x0, 0, z0, u0, 0.0f });
		uint32 v4_s = Vertices.Num();
		Vertices.Add({ x1 * outerRadius, -height / 2, z1 * outerRadius, 1, 1, 1, 1, x1, 0, z1, u1, 0.0f });

		Indices.insert(Indices.end(), { v1_s,v2_s,v3_s, v2_s,v4_s, v3_s, });

		// 내부 측면
		uint32 v1_i = Vertices.Num();
		Vertices.Add({ x0 * innerRadius, height / 2, z0 * innerRadius, 1, 1, 1, 1, -x0, 0, -z0, u0, 1.0f });
		uint32 v2_i = Vertices.Num();
		Vertices.Add({ x1 * innerRadius, height / 2, z1 * innerRadius, 1, 1, 1, 1, -x1, 0, -z1, u1, 1.0f });
		uint32 v3_i = Vertices.Num();
		Vertices.Add({ x0 * innerRadius, -height / 2, z0 * innerRadius, 1, 1, 1, 1, -x0, 0, -z0, u0, 0.0f });
		uint32 v4_i = Vertices.Num();
		Vertices.Add({ x1 * innerRadius, -height / 2, z1 * innerRadius, 1, 1, 1, 1, -x1, 0, -z1, u1, 0.0f });

		Indices.insert(Indices.end(), { v1_i, v3_i,v2_i, v2_i,  v3_i,v4_i });
	}

	return { Vertices, Indices };
}


