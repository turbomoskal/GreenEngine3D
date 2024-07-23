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