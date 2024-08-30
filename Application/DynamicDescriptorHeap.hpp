#pragma once

#include <d3dx12.h>

#include <wrl.h>

#include <cstdint>
#include <memory>
#include <queue>
#include <functional>

class CommandList;
class RootSignature;

class DynamicDescriptorHeap {
public:
	DynamicDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE, uint32_t = 1024);
	virtual ~DynamicDescriptorHeap();
	void StageDescriptors(uint32_t, uint32_t, uint32_t, const D3D12_CPU_DESCRIPTOR_HANDLE);
	void CommitStagedDescriptors(CommandList&, 
		std::function<void(ID3D12GraphicsCommandList*, uint32_t, D3D12_GPU_DESCRIPTOR_HANDLE)>);
	void CommitStagedDescriptorsForDraw(CommandList&);
	void CommitStagedDescriptorsForDispatch(CommandList&);
	D3D12_GPU_DESCRIPTOR_HANDLE CopyDescriptor(CommandList&, D3D12_CPU_DESCRIPTOR_HANDLE);
	void ParseRootSignature(const RootSignature&);
	void Reset();

private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> RequestDescriptorHeap();
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap();
	uint32_t ComputeStaleDescriptorCount() const;
	static const uint32_t _MaxDescriptorTables = 32;
	struct DescriptorTableCache {
		DescriptorTableCache() :
			NumDescriptors(0),
			BaseDescriptor(nullptr){}
		void Reset() {
			NumDescriptors = 0;
			BaseDescriptor = nullptr;
		}
		uint32_t						NumDescriptors;
		D3D12_CPU_DESCRIPTOR_HANDLE*	BaseDescriptor;
	};
	D3D12_DESCRIPTOR_HEAP_TYPE						_DescriptorHeapType;
	uint32_t										_NumDescriptorsPerHeap;
	uint32_t										_DescriptorHandleIncrementSize;
	std::unique_ptr<D3D12_CPU_DESCRIPTOR_HANDLE[]>	_DescriptorHandleCache;
	DescriptorTableCache _DescriptorTableCache[_MaxDescriptorTables];
	uint32_t										_DescriptorTableBitMask;
	uint32_t										_StaleDescriptorTableBitMask;
	using DescriptorHeapTool = std::queue<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> >;
	DescriptorHeapTool								_DescriptorHeapTool;
	DescriptorHeapTool								_AvailableDescriptorHeaps;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	_CurrentDescriptorHeap;
	CD3DX12_GPU_DESCRIPTOR_HANDLE					_CurrentGPUDescriptorHandle;
	CD3DX12_GPU_DESCRIPTOR_HANDLE					_CurrentCPUDescriptorHandle;
	uint32_t										_NumFreeHandles;
};