#pragma once

#include "Buffer.hpp"
#include "ByteAddressBuffer.hpp"

class StructuredBuffer : public Buffer {
public:
	StructuredBuffer(const std::wstring & = L"");
	StructuredBuffer(const D3D12_RESOURCE_DESC&, size_t, size_t, const std::wstring & = L"");
	virtual size_t GetNumElements() const { return _NumElements; }
	virtual size_t GetElementSize() const { return _ElementSize; }
	virtual void CreateViews(size_t, size_t) override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const { 
		return _SRV.GetDescriptorHandle(); 
	}
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override {
		return _UAV.GetDescriptorHandle();
	}
	const ByteAddressBuffer& GetCounterBuffer() const { return _CounterBuffer; }

private:
	size_t					_NumElements;
	size_t					_ElementSize;
	DescriptorAllocation	_SRV;
	DescriptorAllocation	_UAV;
	ByteAddressBuffer		_CounterBuffer;
};