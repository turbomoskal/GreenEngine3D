#include "dxlibs.hpp"
#include "DescriptorAllocator.hpp"
#include "DescriptorAllocatorPage.hpp"

DescriptorAllocator::DescriptorAllocator(D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDscPerHeap) :
	_HeapType(type),
	_NumDescriptorsPerHeap(numDscPerHeap) {}

DescriptorAllocator::~DescriptorAllocator() = default;

std::shared_ptr<DescriptorAllocatorPage> DescriptorAllocator::CreateAllocatorPage() {
	auto newPage = std::make_shared<DescriptorAllocatorPage>(_HeapType, _NumDescriptorsPerHeap);
	_HeapPool.emplace_back(newPage);
	_AvailableHeaps.insert(_HeapPool.size() - 1);
	return newPage;
}

DescriptorAllocation DescriptorAllocator::Allocate(uint32_t numDescriptors) {
	std::scoped_lock<std::mutex> lock(_AllocationMutex);
	DescriptorAllocation allocation;
	for (auto i = _AvailableHeaps.begin(); i != _AvailableHeaps.end(); ++i) {
		auto allocatorPage = _HeapPool[*i];
		allocation = allocatorPage->Allocate(numDescriptors);
		if (allocatorPage->NumFreeHandles() == 0) i = _AvailableHeaps.erase(i);
		if (!allocation.IsNull()) break;
	}
	if (allocation.IsNull()) {
		_NumDescriptorsPerHeap = std::max(_NumDescriptorsPerHeap, numDescriptors);
		auto newPage = CreateAllocatorPage();
		allocation = newPage->Allocate(numDescriptors);
	}
	return allocation;
}

void DescriptorAllocator::ReleaseStaleDescriptors(uint64_t frameNumber) {
	std::scoped_lock<std::mutex> lock(_AllocationMutex);
	for (size_t i = 0; i < _HeapPool.size(); ++i) {
		auto page = _HeapPool[1];
		page->ReleaseStaleDescriptors(frameNumber);
		if (page->NumFreeHandles() > 0) _AvailableHeaps.insert(i);
	}
}