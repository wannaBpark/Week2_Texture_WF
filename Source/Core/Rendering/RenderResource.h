﻿#pragma once

#include "Core/Rendering/ShaderParameterMacros.h"

#include <d3d11.h>
#include <unordered_map>
#include <optional>
#include "Core/HAL/PlatformType.h"

struct FRenderResource {
	EPrimitiveType PrimitiveType;												// 최초 정의
	InputLayoutType InputLayoutType = InputLayoutType::POSCOLOR;
	D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//union {
		uint32 numVertices = 0;					// Draw (numVertices, ...) 
		//uint32 numIndices;						// Draw Indexed (numIndices, ...)
	//};
	uint32 Stride				   { 0 };
	uint32 VertexShaderIndex       { 0 };
	uint32 PixelShaderIndex        { 0 };
	uint32 VertexConstantIndex     { 0 };
	uint32 PixelConstantIndex      { 0 };
	uint32 GeometryShaderIndex     { 0 };

	std::optional<std::vector<uint32>> ShaderResourceViewIndices; // 다중 SRV [없을 수도 있음]
};


// 입력 레이아웃 정의
const std::unordered_map<InputLayoutType, std::vector<D3D11_INPUT_ELEMENT_DESC>> InputLayouts = {
	{ InputLayoutType::POSCOLOR, {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	}},
	{ InputLayoutType::POSCOLORNORMAL, {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	}},
	{ InputLayoutType::POSNORMALTEX, {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,   0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	}},
	{ InputLayoutType::POSCOLORNORMALTEX, {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	}},
};