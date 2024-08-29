#pragma once

#include "Buffer.hpp"
#include "DescriptorAllocation.hpp"

class ConstantBuffer : public Buffer {
public:
	ConstantBuffer(const std::wstring & = L"");
	virtual ~ConstantBuffer();
	virtual void CreateViews(size_t, size_t) override;
	size_t GetSizeInBytes() const { return _SizeInBytes; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetConstantBufferView() const {
		return _ConstantBufferView.GetDescriptorHandle();
	}
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override;

private:
	size_t					_SizeInBytes;
	DescriptorAllocation	_ConstantBufferView;
};