#pragma once

#include "DescriptorAllocation.hpp"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include <memory>
#include <string>

class CommandQueue;
class DescriptorAllocator;
class Game;
class Window;

class Application {
public:
	static void Create(HINSTANCE);
	static void Destroy();
	static Application& Get();
	bool IsTearingSupported() const;
	DXGI_SAMPLE_DESC GetMultisampleQualityLevels(DXGI_FORMAT, uint32_t, 
		D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE) const;
	std::shared_ptr<Window> CreateRenderWindow(const std::wstring&, int, int, bool = true);
	void DestroyWindow(const std::wstring&);
	void DestroyWindow(std::shared_ptr<Window>);
	std::shared_ptr<Window> GetWindowByName(const std::wstring&);
	int Run(std::shared_ptr<Game>);
	void Quit(int = 0);
	Microsoft::WRL::ComPtr<ID3D12Device2> GetDevice() const;
	std::shared_ptr<CommandQueue> GetCommandQueue(
		D3D12_COMMAND_LIST_TYPE = D3D12_COMMAND_LIST_TYPE_DIRECT) const;
	void Flush();
	DescriptorAllocation AllocateDescriptors(D3D12_DESCRIPTOR_HEAP_TYPE, uint32_t = 1);
	void ReleaseStaleDescriptors(uint64_t);
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(uint32_t, 
		D3D12_DESCRIPTOR_HEAP_TYPE);
	uint32_t GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE) const;
	static uint64_t GetFrameCount() { return _FrameCount; }

protected:
	Application(HINSTANCE);
	virtual ~Application();
	void Initialize();
	Microsoft::WRL::ComPtr<IDXGIAdapter4> GetAdapter(bool);
	Microsoft::WRL::ComPtr<ID3D12Device2> CreateDevice(Microsoft::WRL::ComPtr<IDXGIAdapter4>);
	bool CheckTearingSupport;

private:
	friend LRESULT CALLBACK WndProc(HWND, uint32_t, WPARAM, LPARAM);
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	HINSTANCE								_HInstance;
	Microsoft::WRL::ComPtr<ID3D12Device2>	_D3D12Device;
	std::shared_ptr<CommandQueue>			_DirectCommandQueue;
	std::shared_ptr<CommandQueue>			_ComputeCommandQueue;
	std::shared_ptr<CommandQueue>			_CopyCommandQueue;
	std::unique_ptr<DescriptorAllocator> 
		_DescriptorAllocators[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	bool									_TearingSupport;
	static uint64_t							_FrameCount;
};