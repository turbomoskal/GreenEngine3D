/*
*/

#pragma once

#include "LangHeaders.hpp"
#include "WinHeaders.hpp"
#include "DXHeaders.hpp"
using namespace Microsoft::WRL;

inline void ThrowIfFailed(HRESULT hCode) {
	if (FAILED(hCode)) {
		throw std::exception("Ah shit, here we go again.\n", hCode);
	}
}

class Queue {
public:
	Queue(ComPtr<ID3D12Device2>, D3D12_COMMAND_LIST_TYPE);
	virtual ~Queue();

	ComPtr<ID3D12GraphicsCommandList2> GetCommandList();
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	uint64_t ExecuteCommandList(ComPtr<ID3D12GraphicsCommandList2>);
	uint64_t Signal();

	bool IsFenceComplete(uint64_t) const;
	void WaitForFenceValue(uint64_t);
	void Flush();
protected:
	ComPtr<ID3D12CommandAllocator> CreateCommandAllocator();
	ComPtr<ID3D12GraphicsCommandList2> CreateCommandList(ComPtr<ID3D12CommandAllocator>);
private:
	struct CommandAllocatorEntry {
		uint64_t fenceValue;
		ComPtr<ID3D12CommandAllocator> commandAllocator;
	};

	using _CommandAllocatorQueue = std::queue<CommandAllocatorEntry>;
	using _CommandListQueue = std::queue<ComPtr<ID3D12GraphicsCommandList2>>;

	D3D12_COMMAND_LIST_TYPE CommandListType;
	ComPtr<ID3D12Device2> Device;
	ComPtr<ID3D12CommandQueue> CommandQueue;
	ComPtr<ID3D12Fence> Fence;
	HANDLE FenceEvent;
	uint64_t FenceValue;
	_CommandAllocatorQueue CommandAllocatorQueue;
	_CommandListQueue CommandListQueue;
};