#pragma once

#include "Buffer.hpp"
#include "DescriptorAllocation.hpp"

#include <d3dx12.h>

class ByteAddressBuffer : public Buffer {
public:
	ByteAddressBuffer(const std::wstring & = L"");
	ByteAddressBuffer(const D3D12_RESOURCE_DESC&, size_t, size_t, const std::wstring & = L"");
	size_t GetBufferSize() const { return _BufferSize; }
	virtual void CreateViews(size_t, size_t) override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const override { 
		return _SRV.GetDescriptorHandle(); 
	}
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override {
		return _UAV.GetDescriptorHandle();
	}
private:
	size_t					_BufferSize;
	DescriptorAllocation	_SRV;
	DescriptorAllocation	_UAV;
};