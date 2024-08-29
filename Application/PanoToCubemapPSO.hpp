#pragma once

#include "RootSignature.hpp"
#include "DescriptorAllocation.hpp"

#include <cstdint>

struct PanoToCubemapCB {
	uint32_t CubemapSize;
	uint32_t FirstMip;
	uint32_t NumMips;
};

namespace PanoToCubemapRS {
	enum {
		PanoToCubemapCB,
		SrcTexture,
		DstMips,
		NumRootParameters
	};
}

class PanoToCubemapPSO {
public:
	PanoToCubemapPSO();
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