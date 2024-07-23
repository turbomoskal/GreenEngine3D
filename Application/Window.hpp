/*
*		Window
*/

#pragma once
#include "WinHeaders.hpp"
#include "LangHeaders.hpp"
#include "DXHeaders.hpp"

#include "Event.hpp"
#include "HighPerfomanceClock.hpp"
using namespace Microsoft::WRL;

class Renderer;

class Window {
public:
	// ?THinking its unecessary
	static const auto BufferCount = 3u;
	HWND GetWindowHandle() const;
	void Destroy();
	D2D1_SIZE_U GetClientSize() const;
	bool CheckVSyncEnabled() const;
	void SetVSyncState(bool);
	void ToggleVSync();
	bool CheckFullscreenEnabled() const;
	void SetFullscreenState(bool);
	void ToggleFullscreen();
	void Show();
	void Hide();
	// ?Is this necessary? Maybe delete and use graphics
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentRenderTargetView() const;
	ComPtr<ID3D12Resource> GetCurrentBackBuffer() const;
protected:
	friend long long __stdcall WndProc(HWND, UINT, WPARAM, LPARAM);
	friend class Engine;
	friend class Renderer;

	Window() = delete;
	Window(HWND, D2D1_SIZE_U, bool);
	virtual ~Window();

	void RegisterCallbacks(std::shared_ptr<Renderer>);
	virtual void OnUpdate(UpdateEvent&);
	virtual void OnRender(RenderEvent&);
	virtual void OnResize(ResizeEvent&);
	virtual void OnKeyPressed(KeyEvent&);
	virtual void OnKeyReleased(KeyEvent&);
	virtual void OnMouseMoved(MouseMotionEvent&);
	virtual void OnMousePressed(MouseButtonEvent&);
	virtual void OnMouseReleased(MouseButtonEvent&);
	virtual void OnMouseWheel(MouseWheelEvent&);
	// ?Unecessary
	ComPtr<IDXGISwapChain4> CreateSwapChain();
	void UpdateRenderTargetViews();
private:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	HWND Hwnd;
	D2D1_SIZE_U ClientSize;
	bool VSyncState;
	bool FullscreenState;
	bool TearingSupport;
	Clock UpdateClock;
	Clock RenderClock;
	uint64_t FrameCounter;
	RECT WindowRect;
	std::weak_ptr<Renderer> ptrGame;
};