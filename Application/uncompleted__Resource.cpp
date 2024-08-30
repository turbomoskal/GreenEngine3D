#include "Resource.hpp"

D3D12_RESOURCE_DESC Resource::GetD3D12ResourceDesc() const {
	D3D12_RESOURCE_DESC resDesc = {};
	if (_D3D12Resource) resDesc = _D3D12Resource->GetDesc();
	return resDesc;
}
/*
* TODO:		Sources
* 
* Application
* CommandList
* CommandQueue
* DescriptionAllocatorPage
* dxlibs
* DynamicDescriptorHeap
* Game
* GenerateMipsPSO
* IndexBuffer
* Mesh
* PanoToCubemapPSO
* RenderTarget
* Resource
* ResourceStateTracker
* RootSignature
* StructuredBuffer
* Texture
* UploadBuffer
* VertexBuffer
* Window
*/