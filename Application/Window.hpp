#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_5.h>

#include "Event.hpp"
#include "HighPerfomanceClock.hpp"
#include "RenderTarget.hpp"
#include "Texture.hpp"

#include <memory>

class Game;
class Texture;

class Window : public std::enable_shared_from_this<Window> {
public:
	static const uint32_t BufferCount = 3;
	HWND GetWindowHandle() const;
	void Initialize();
	void Destroy();
	const std::wstring& GetWindowName() const;
	int GetClientWidth() const;
	int GetClientHeight() const;
	bool IsVSync() const;
	void SetVSync(bool);
	void ToggleVSync();
	bool IsFullscreen() const;
	void SetFullscreen(bool);
	void ToggleFullscreen();
	void Show();
	void Hide();
	const RenderTarget& GetRenderTarget() const;
	uint32_t Present(const Texture & = Texture());

protected:
	friend LRESULT CALLBACK WndProc(HWND, uint32_t, WPARAM, LPARAM);
	friend class Application;
	friend class Game;
	Window() = delete;
	Window(HWND, const std::wstring&, int, int, bool);
	virtual ~Window();
	void RegisterCallbacks(std::shared_ptr<Game>);
	virtual void OnUpdate(UpdateEventArgs&);
	virtual void OnRender(RenderEventArgs&);
	virtual void OnKeyPressed(KeyEventArgs&);
	virtual void OnKeyReleased(KeyEventArgs&);
	virtual void OnMouseMoved(MouseMotionEventArgs&);
	virtual void OnMouseButtonPressed(MouseButtonEventArgs&);
	virtual void OnMouseButtonReleased(MouseButtonEventArgs&);
	virtual void OnMouseWheel(MouseWheelEventArgs&);
	virtual void OnResize(ResizeEventArgs&);
	Microsoft::WRL::ComPtr<IDXGISwapChain4> CreateSwapChain();
	void UpdateRenderTargetViews();

private:
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	HWND										_Hwnd;
	std::wstring								_WindowName;
	int											_ClientWidth;
	int											_ClientHeight;
	bool										_VSync;
	bool										_Fullscreen;
	Clock										_UpdateClock;
	Clock										_RenderClock;
	uint64_t									_FenceValues[BufferCount];
	uint64_t									_FrameValues[BufferCount];
	std::weak_ptr<Game>							_PGame;
	Microsoft::WRL::ComPtr<IDXGISwapChain4>		_DxgiSwapChain;
	Texture										_BackBufferTextures[BufferCount];
	mutable RenderTarget						_RenderTarget;
	uint32_t									_CurrentBackBufferIndex;
	RECT										_WindowRect;
	bool										_IsTearingSupported;
	int											_PreviousMouseX;
	int											_PreviousMouseY;
};