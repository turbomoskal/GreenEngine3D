#pragma once

#include "Buffer.hpp"

class IndexBuffer : public Buffer {
public:
	IndexBuffer(const std::wstring & = L"");
	virtual ~IndexBuffer();
	virtual void CreateViews(size_t, size_t) override;
	size_t GetNumIndicies() const { return _NumIndicies; }
	DXGI_FORMAT GetIndexFormat() const { return _IndexFormat; }
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() const { return _IndexBufferView; }
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override;

private:
	size_t						_NumIndicies;
	DXGI_FORMAT					_IndexFormat;
	D3D12_INDEX_BUFFER_VIEW		_IndexBufferView;
};