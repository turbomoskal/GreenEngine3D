#pragma once

#include "DescriptorAllocation.hpp"

#include <d3dx12.h>

#include <wrl.h>

#include <map>
#include <memory>
#include <mutex>
#include <queue>

class DescriptorAllocatorPage : public std::enable_shared_from_this<DescriptorAllocatorPage> {
	DescriptorAllocatorPage(D3D12_DESCRIPTOR_HEAP_TYPE, uint32_t);
	D3D12_DESCRIPTOR_HEAP_TYPE GetHeapType() const;
	bool HasSpace(uint32_t) const;
	uint32_t NumFreeHandles() const;
	DescriptorAllocation Allocate(uint32_t);
	void Free(DescriptorAllocation&&, uint64_t);
	void ReleaseStaleDescriptors(uint64_t);

protected:
	uint32_t ComputeOffset(D3D12_CPU_DESCRIPTOR_HANDLE);
	void AddNewBlock(uint32_t, uint32_t);
	void FreeBlock(uint32_t, uint32_t);

private:
	struct FreeBlockInfo;
	using FreeListByOffset = std::map<uint32_t, FreeBlockInfo>;
	using FreeListBySize = std::multimap<uint32_t, FreeListByOffset::iterator>;
	struct FreeBlockInfo {
		FreeBlockInfo(uint32_t size) :
			_Size(size) {}
		uint32_t _Size;
		FreeListBySize::iterator FreeListBySizeIt;
	};
	struct StaleDescriptorInfo {
		StaleDescriptorInfo(uint32_t offset, uint32_t size, uint64_t frame) :
			_Offset(offset),
			_Size(size),
			_FrameNumber(frame) {}
		uint32_t _Offset;
		uint32_t _Size;
		uint64_t _FrameNumber;
	};
	using StaleDescriptorQueue = std::queue<StaleDescriptorInfo>;
	FreeListByOffset _FreeListByOffset;
	FreeListBySize _FreeListBySize;
	StaleDescriptorQueue _StaleDescriptors;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _D3D12DescriptorHeap;
	D3D12_DESCRIPTOR_HEAP_TYPE _HeapType;
	CD3DX12_CPU_DESCRIPTOR_HANDLE _BaseDescriptor;
	uint32_t _DescriptorHandleIncrementSize;
	uint32_t _NumDescriptorsInHeap;
	uint32_t _NumFreeHandles;
	std::mutex _AllocationMutex;
};