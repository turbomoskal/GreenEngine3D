#include "dxlibs.hpp"
#include "ByteAddressBuffer.hpp"
#include "Application.hpp"

ByteAddressBuffer::ByteAddressBuffer(const std::wstring& name) :
	Buffer(name) {
	_SRV = Application::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	_UAV = Application::Get().AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

ByteAddressBuffer::ByteAddressBuffer(const D3D12_RESOURCE_DESC& resDesc, size_t numElements,
	size_t elementSize, const std::wstring& name) :
	Buffer(resDesc, numElements, elementSize) {}

void ByteAddressBuffer::CreateViews(size_t numElements, size_t elementSize) {
	auto device = Application::Get().GetDevice();
	_BufferSize = Math::AlignUp(numElements * elementSize, 4);
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Buffer.NumElements = (uint32_t)_BufferSize / 4;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_RAW;
	device->CreateShaderResourceView(_D3D12Resource.Get(), &srvDesc, _SRV.GetDescriptorHandle());
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	uavDesc.Buffer.NumElements = (uint32_t)_BufferSize / 4;
	uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_RAW;
	device->CreateUnorderedAccessView(_D3D12Resource.Get(), nullptr, &uavDesc, 
		_UAV.GetDescriptorHandle());
}