#pragma once

#include "Buffer.hpp"

class VertexBuffer :public Buffer {
public:
	VertexBuffer(const std::wstring & = L"");
	virtual ~VertexBuffer();
	virtual void CreateViews(size_t, size_t) override;
	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const { return _VertexBufferView; }
	size_t GetNumVertices() const { return _NumVertices; }
	size_t GetVertexStride() const { return _VertexStride; }
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override;

private:
	size_t						_NumVertices;
	size_t						_VertexStride;
	D3D12_VERTEX_BUFFER_VIEW	_VertexBufferView;
};