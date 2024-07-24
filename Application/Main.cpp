/*
*		GreenEngine3D: Application main code
*		...
* 
*		turbomoskal and ... (c) 2024
*/

#include "LangHeaders.hpp"
#include "WinHeaders.hpp"
#include "DXHeaders.hpp"

void ReportLiveObjects() {
	IDXGIDebug1* dxgiDebug;
	DXGIGetDebugInterface1(0, IID_PPV_ARGS(&dxgiDebug));

	dxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
	dxgiDebug->Release();
}

void ParseCommandLineArguments(D2D1_SIZE_U& _ClientSize, bool& _UseWarp, bool& _Debug) {
	int argc;
	wchar_t** argv = ::CommandLineToArgvW(::GetCommandLineW(), &argc);
	auto clientWidth(0u);
	auto clientHeight(0u);

	for (auto i(0); i < argc; i++) {
		if (::wcscmp(argv[i], L"-w") == 0 || ::wcscmp(argv[i], L"--width") == 0) {
			clientWidth = ::wcstol(argv[++i], nullptr, 10); //? What is 10?
		}
		if (::wcscmp(argv[i], L"-h") == 0 || ::wcscmp(argv[i], L"--height") == 0) {
			clientHeight = ::wcstol(argv[++i], nullptr, 10);
		}
		if (::wcscmp(argv[i], L"-warp") == 0 || ::wcscmp(argv[i], L"--warp") == 0) {
			_UseWarp = true;
		}
		if (::wcscmp(argv[i], L"-d") == 0 || ::wcscmp(argv[i], L"--debug") == 0) {
			_Debug = true;
		}
	}

	_ClientSize = D2D1::SizeU(clientWidth, clientHeight);
	::LocalFree(argv);
}

int __stdcall wWinMain(
	_In_ HINSTANCE		hInstance,
	_In_opt_ HINSTANCE	hPrevInstance,
	_In_ LPWSTR			lpCmdLine,
	_In_ int			nCmdShow)
{
	int retCode(0);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WCHAR path[MAX_PATH];
	HMODULE hModule = GetModuleHandleW(NULL);
	if (GetModuleFileNameW(hModule, path, MAX_PATH) > 0) {
		PathRemoveFileSpecW(path);
		SetCurrentDirectoryW(path);
	}

	try {
		
	}
	catch (std::exception& e) {
		std::string msg = e.what();
		OutputDebugStringA(msg.c_str());
	}

	return retCode;
}