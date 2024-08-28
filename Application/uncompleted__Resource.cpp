#include "Resource.hpp"

D3D12_RESOURCE_DESC Resource::GetD3D12ResourceDesc() const {
	D3D12_RESOURCE_DESC resDesc = {};
	if (_D3D12Resource) resDesc = _D3D12Resource->GetDesc();
	return resDesc;
}