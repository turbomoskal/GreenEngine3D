/*
* 
*/

#include "Engine.hpp"
#include "WinHeaders.hpp"
#include "LangHeaders.hpp"

#include "Renderer.hpp"
#include "Window.hpp"

using namespace Microsoft::WRL;

constexpr wchar_t g_WindowClassName[] = L"GreenEngine3D";

using WindowPtr = std::shared_ptr<Window>;
using WindowMap = std::map<HWND, WindowPtr>;

static Engine* gs_Singleton = nullptr;
static WindowMap gs_WindowMap;

// !Wrapper for Window to allow shared ptrs for class
struct MakeWindow : public Window {
	MakeWindow(HWND _Hwnd, D2D1_SIZE_U _ClientSize, bool _VSync) :
		Window(_Hwnd, _ClientSize, _VSync) {}
};

// !Check for tearing support
bool CheckTearingSupport() {
	bool allowTearing(false);

	// !Rather then create DXGI 1.5 factory directly, I create
	// !DXGI 1.4 factory and query for 1.5 interface. This is
	// !to enable graphics debug tools which will be deprecated
	// !in 1.5 interface until future updates
	ComPtr<IDXGIFactory4> ptrDXGIFactory4;
	if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&ptrDXGIFactory4)))) {
		ComPtr<IDXGIFactory5> ptrDXGIFactory5;
		if (SUCCEEDED(ptrDXGIFactory4.As(&ptrDXGIFactory5))) {
			if (FAILED(ptrDXGIFactory5->CheckFeatureSupport(
				DXGI_FEATURE_PRESENT_ALLOW_TEARING, 
				&allowTearing, sizeof(allowTearing)))) {
				allowTearing = false;
			}
		}
	}
	
	return (allowTearing == true);
}

Engine::Engine(HINSTANCE _MainInstance) :
	MainInstance(_MainInstance),
	TearingSupport(CheckTearingSupport()) {
	SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	WNDCLASSEXW wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEXW);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = &WndProc;
	wndClass.hInstance = MainInstance;
	wndClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIconW(MainInstance, MAKEINTRESOURCEW(IDI_ICON1));
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = g_WindowClassName;
	wndClass.hIconSm = LoadIconW(MainInstance, MAKEINTRESOURCEW(IDI_ICON1));

	if (!RegisterClassExW(&wndClass)) {
		// ?What is LANG_RUSSIAN
		// TODO: Replace with exception and external WinForm app to show more info
		MessageBoxExW(nullptr, L"Unable to register window class", L"Error", MB_OK | MB_ICONERROR, LANG_RUSSIAN);
	}
}

void Engine::Create(HINSTANCE _Instance) {
	if (!gs_Singleton) {
		gs_Singleton = new Engine(_Instance);
	}
}

Engine& Engine::Get() {
	assert(gs_Singleton);
	return *gs_Singleton;
}

void Engine::Destroy() {
	if (gs_Singleton) {
		assert(gs_WindowMap.empty() && "All windows should be destroyed before application");
		delete gs_Singleton;
		gs_Singleton = nullptr;
	}
}