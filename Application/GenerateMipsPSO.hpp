#pragma once

#include "RootSignature.hpp"
#include "DescriptorAllocation.hpp"

#include <d3d12.h>
#include <DirectXMath.h>
#include <wrl.h>

struct alignas(16) GenerateMipsCB {
	uint32_t			SrcMipLevel;
	uint32_t			NumMipLevels;
	uint32_t			SrcDimension;
	uint32_t			IsSRGB;
	DirectX::XMFLOAT2	TexelSize;
};

namespace GenerateMips {
	enum {
		GenerateMipsCB,
		SrcMip,
		OutMip,
		NumRootParameters
	};
}

class GenerateMipsPSO {
public:
	GenerateMipsPSO();
	const RootSignature& GetRootSignature() const { return _RootSignature; }
	Microsoft::WRL::ComPtr<ID3D12PipelineState> GetPipelineState() const { return _PipelineState; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetDefaultUAV() const {
		return _DefaultUAV.GetDescriptorHandle();
	}

private:
	RootSignature									_RootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>		_PipelineState;
	DescriptorAllocation							_DefaultUAV;
};