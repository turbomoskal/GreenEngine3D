/*
*/

#include "Queue.hpp"

inline void ThrowIfFailed(HRESULT hCode) {
	if (FAILED(hCode)) {
		throw std::exception("Ah shit, here we go again.\n", hCode);
	}
}

Queue::Queue(ComPtr<ID3D12Device2> _Device, D3D12_COMMAND_LIST_TYPE _ListType) :
	CommandListType(_ListType),
	Device(_Device),
	FenceValue(0uLL) {
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};

	queueDesc.Type = _ListType;
	queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0u;

	ThrowIfFailed(Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&CommandQueue)));
	ThrowIfFailed(Device->CreateFence(FenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence)));

	FenceEvent = ::CreateEventW(nullptr, false, false, nullptr);
	assert(FenceEvent && "Failed to create fence event handle.");
}

Queue::~Queue() = default;

uint64_t Queue::Signal() {
	auto fenceValue = ++FenceValue;
	CommandQueue->Signal(Fence.Get(), fenceValue);
	return fenceValue;
}

bool Queue::IsFenceComplete(uint64_t fenceValue) const {
	return Fence->GetCompletedValue() >= fenceValue;
}

void Queue::WaitForFenceValue(uint64_t fenceValue) {
	if (!IsFenceComplete(fenceValue)) {
		Fence->SetEventOnCompletion(fenceValue, FenceEvent);
		::WaitForSingleObject(FenceEvent, DWORD_MAX);
	}
}

void Queue::Flush() {
	WaitForFenceValue(Signal());
}

ComPtr<ID3D12CommandAllocator> Queue::CreateCommandAllocator() {
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ThrowIfFailed(Device->CreateCommandAllocator(CommandListType, IID_PPV_ARGS(&commandAllocator)));
	return commandAllocator;
}

ComPtr<ID3D12GraphicsCommandList2> Queue::CreateCommandList(ComPtr<ID3D12CommandAllocator> commandAllocator) {
	ComPtr<ID3D12GraphicsCommandList2> commandList;
	ThrowIfFailed(Device->CreateCommandList(0u, CommandListType, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
	return commandList;
}

ComPtr<ID3D12GraphicsCommandList2> Queue::GetCommandList() {
	ComPtr<ID3D12GraphicsCommandList2> commandList;
	ComPtr<ID3D12CommandAllocator> commandAllocator;

	if (!CommandAllocatorQueue.empty() && IsFenceComplete(CommandAllocatorQueue.front().fenceValue)) {
		commandAllocator = CommandAllocatorQueue.front().commandAllocator;
		CommandAllocatorQueue.pop();
		ThrowIfFailed(commandAllocator->Reset());
	}
	else {
		commandAllocator = CreateCommandAllocator();
	}

	if (!CommandListQueue.empty()) {
		commandList = CommandListQueue.front();
		CommandListQueue.pop();
		ThrowIfFailed(commandList->Reset(commandAllocator.Get(), nullptr));
	}
	else {
		commandList = CreateCommandList(commandAllocator);
	}

	ThrowIfFailed(commandList->SetPrivateDataInterface(__uuidof(ID3D12CommandAllocator), commandAllocator.Get()));
	return commandList;
}

uint64_t Queue::ExecuteCommandList(ComPtr<ID3D12GraphicsCommandList2> commandList) {
	commandList->Close();

	ID3D12CommandAllocator* commandAllocator;
	uint32_t dataSize = sizeof(commandAllocator);

	ThrowIfFailed(commandList->GetPrivateData(__uuidof(ID3D12CommandAllocator), &dataSize, &commandAllocator));

	ID3D12CommandList* const pptrCommandLists[] = {
		commandList.Get()
	};
	CommandQueue->ExecuteCommandLists(1, pptrCommandLists);
	auto fenceValue = Signal();

	CommandAllocatorQueue.emplace(CommandAllocatorEntry{ fenceValue, commandAllocator });
	CommandListQueue.push(commandList);

	commandAllocator->Release();
	return fenceValue;
}

ComPtr<ID3D12CommandQueue> Queue::GetCommandQueue() const {
	return CommandQueue;
}