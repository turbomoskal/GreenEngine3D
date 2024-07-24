/*
* 
*/
#pragma once

#if defined(max)
#undef max
#endif
#if defined(min)
#undef min
#endif

#include "LangHeaders.hpp"
#include "WinHeaders.hpp"
#include "DXHeaders.hpp"

#include "Queue.hpp"


using namespace Microsoft::WRL;

class Direct3D {
private:
	static const int BackBufferLength = 3;
	bool EnableDebug = false;

	HWND ClientInstance;
	RECT ClientRect;

	ComPtr<ID3D12Debug> ptrDebugInterface;
	ComPtr<ID3D12Device2> ptrDevice;
	ComPtr<ID3D12CommandQueue> ptrQueue;
	ComPtr<IDXGISwapChain4> ptrSwapChain;
	ComPtr<ID3D12Resource> ptrBackBuffers[BackBufferLength];
	ComPtr<ID3D12GraphicsCommandList> ptrCommandList;
	ComPtr<ID3D12CommandAllocator> ptrCommandAllocators[BackBufferLength];
	ComPtr<ID3D12DescriptorHeap> ptrRTVDescriptorHeap;

	uint32_t RTVDescriptorSize;
	uint32_t CurrentBackBufferIndex;
public:
	void EnableDebugLayer();
};