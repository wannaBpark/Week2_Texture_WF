#pragma once
#include <unordered_map>
#include <d3d11.h>
#include <wrl/client.h>
#include "Primitive/PrimitiveVertices.h"

struct BufferInfo
{
public:
	BufferInfo() = default;
	BufferInfo(ID3D11Buffer* InBuffer, int BufferSize)
	{
		Buffer = InBuffer;
		Size = BufferSize;
	}

	ID3D11Buffer* GetBuffer() const { return Buffer.Get(); }
	int GetSize() const { return Size; }
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;
	int Size;
};

class FBufferCache
{
private:
	std::unordered_map <EPrimitiveType, BufferInfo> Cache;

public:
	FBufferCache();
	~FBufferCache();

	void Init();
	BufferInfo GetBufferInfo(EPrimitiveType Type);

private :
	BufferInfo CreateVertexBufferInfo(EPrimitiveType Type);
};

