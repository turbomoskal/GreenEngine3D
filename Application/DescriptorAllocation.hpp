#pragma once

#include <d3d12.h>

#include <cstdint>
#include <memory>

class DescriptorAllocatorPage;

class DescriptorAllocation {
public:
	DescriptorAllocation();
	DescriptorAllocation(D3D12_CPU_DESCRIPTOR_HANDLE, uint32_t, uint32_t, std::shared_ptr<DescriptorAllocatorPage>);
	~DescriptorAllocation();
	DescriptorAllocation(const DescriptorAllocation&) = delete;
	DescriptorAllocation& operator=(const DescriptorAllocation&) = delete;
	DescriptorAllocation(DescriptorAllocation&&);
	DescriptorAllocation& operator=(DescriptorAllocation&&);

	bool IsNull() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandle(uint32_t = 0) const;
	uint32_t GetNumHandles() const;
	std::shared_ptr<DescriptorAllocatorPage> GetDescriptorAllocatorPage() const;

private:
	void Free();
	D3D12_CPU_DESCRIPTOR_HANDLE					_Descriptor;
	uint32_t									_NumHandles;
	uint32_t									_DescriptorSize;
	std::shared_ptr<DescriptorAllocatorPage>	_Page;
};