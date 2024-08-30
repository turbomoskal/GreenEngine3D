#include "dxlibs.hpp"
#include "ConstantBuffer.hpp"
#include "Application.hpp"
#include <d3dx12.h>

ConstantBuffer::ConstantBuffer(const std::wstring& name) :
	Buffer(name),
	_SizeInBytes(0) {
	_ConstantBufferView = Application::Get().AllocateDescriptors(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

ConstantBuffer::~ConstantBuffer() {}

void ConstantBuffer::CreateViews(size_t numElements, size_t elementSize) {
	_SizeInBytes = numElements * elementSize;
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3d12ConstantBufferViewDesc;
	d3d12ConstantBufferViewDesc.BufferLocation = _D3D12Resource->GetGPUVirtualAddress();
	d3d12ConstantBufferViewDesc.SizeInBytes = static_cast<uint32_t>(
		Math::AlignUp(_SizeInBytes, 16));
	auto device = Application::Get().GetDevice();
	device->CreateConstantBufferView(&d3d12ConstantBufferViewDesc, 
		_ConstantBufferView.GetDescriptorHandle());
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetShaderResourceView(
	const D3D12_SHADER_RESOURCE_VIEW_DESC*) const {
	throw std::exception("ConstantBuffer::GetShaderResourceView should not be called");
}

D3D12_CPU_DESCRIPTOR_HANDLE ConstantBuffer::GetUnorderedAccessView(
	const D3D12_UNORDERED_ACCESS_VIEW_DESC*) const {
	throw std::exception("ConstantBuffer::GetUnorderedAccessView should not be called");
}