/*
*/

#include "Direct3D.hpp"

void Direct3D::EnableDebugLayer() {
	if (EnableDebug) {
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&ptrDebugInterface)));
		ptrDebugInterface->EnableDebugLayer();
	}
}