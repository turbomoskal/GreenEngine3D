#pragma once
#include "DescriptorAllocation.hpp"

#include <d3dx12.h>

#include <cstdint>
#include <mutex>
#include <memory>
#include <set>
#include <vector>

class DescriptorAllocatorPage;

class DescriptorAllocator {
public:
	DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE, uint32_t = 256);
	virtual ~DescriptorAllocator();
	DescriptorAllocation Allocate(uint32_t = 1);
	void ReleaseStaleDescriptors(uint64_t);

private:
	using DescriptorHeapPool = std::vector<std::shared_ptr<DescriptorAllocatorPage> >;
	std::shared_ptr<DescriptorAllocatorPage> CreateAllocatorPage();
	D3D12_DESCRIPTOR_HEAP_TYPE	_HeapType;
	uint32_t					_NumDescriptorsPerHeap;
	DescriptorHeapPool			_HeapPool;
	std::set<size_t>			_AvailableHeaps;
	std::mutex					_AllocationMutex;
};