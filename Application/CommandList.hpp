#pragma once

#include "TextureUsage.hpp"

#include <d3d12.h>
#include <wrl.h>

#include <map>
#include <memory>
#include <mutex>
#include <vector>

class Buffer;
class ByteAddressBuffer;
class ConstantBuffer;
class DynamicDescriptorHeap;
class GenerateMipsPSO;
class IndexBuffer;
class PanoToCubemapPSO;
class RenderTarget;
class Resource;
class ResourceStateTracker;
class StructuredBuffer;
class RootSignature;
class Texture;
class UploadBuffer;
class VertexBuffer;

class CommandList {
public:
	CommandList(D3D12_COMMAND_LIST_TYPE);
	virtual ~CommandList();
	D3D12_COMMAND_LIST_TYPE GetCommandListType() const { return _D3D12CommandListType; }
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2> GetGraphicsCommandList() const {
		return _D3D12CommandList;
	}
	void TransitionBarrier(const Resource&, D3D12_RESOURCE_STATES, 
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, bool = false);
	void TransitionBarrier(Microsoft::WRL::ComPtr<ID3D12Resource>, D3D12_RESOURCE_STATES, 
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, bool = false);
	void UAVBarrier(const Resource&, bool = false);
	void UAVBarrier(Microsoft::WRL::ComPtr<ID3D12Resource>, bool = false);
	void AliasingBarrier(const Resource&, const Resource&, bool = false);
	void AliasingBarrier(Microsoft::WRL::ComPtr<ID3D12Resource>, 
		Microsoft::WRL::ComPtr<ID3D12Resource>, bool = false);
	void FlushResourceBarriers();
	void CopyResource(Resource&, const Resource&);
	void CopyResource(Microsoft::WRL::ComPtr<ID3D12Resource>, 
		Microsoft::WRL::ComPtr<ID3D12Resource>);
	void ResolveSubresource(Resource&, const Resource&, uint32_t = 0, uint32_t = 0);
	void CopyVertexBuffer(VertexBuffer&, size_t, size_t, const void*);
	template <typename T> void CopyVertexBuffer(VertexBuffer& vertexBuffer, 
		const std::vector<T>& vertexBufferData) {
		CopyVertexBuffer(vertexBuffer, vertexBufferData.size(), sizeof(T), vertexBufferData.data());
	}
	void CopyIndexBuffer(IndexBuffer&, size_t, DXGI_FORMAT, const void*);
	template <typename T> void CopyIndexBuffer(IndexBuffer& indexBuffer,
		const std::vector<T>& indexBufferData) {
		assert(sizeof(T) == 2 || sizeof(T) == 4);
		DXGI_FORMAT indexFormat = (sizeof(T) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
		CopyIndexBuffer(indexBuffer, indexBufferData.size(), indexFormat, indexBufferData.data());
	}
	void CopyByteAddressBuffer(ByteAddressBuffer&, size_t, const void*);
	template <typename T> void CopyByteAddressBuffer(ByteAddressBuffer& byteAddressBuffer,
		const T& data) {
		CopyByteAddressBuffer(byteAddressBuffer, sizeof(T), &data);
	}
	void CopyStructuredBuffer(StructuredBuffer&, size_t, size_t, const void*);
	template <typename T> void CopyStructuredBuffer(StructuredBuffer& structuredBuffer,
		const std::vector<T>& bufferData) {
		CopyStructuredBuffer(structuredBuffer, bufferData.size(), sizeof(T), bufferData.data());
	}
	void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY);
	void LoadTextureFromFile(Texture&, const std::wstring&, TextureUsage = TextureUsage::Albedo);
	void ClearTexture(const Texture&, const float[4]);
	void ClearDepthStencilTexture(const Texture&, D3D12_CLEAR_FLAGS, float = 1.f, uint8_t = 0);
	void GenerateMips(Texture&);
	void PanoToCubemap(Texture&, const Texture&);
	void CopyTextureSubresource(Texture&, uint32_t, uint32_t, D3D12_SUBRESOURCE_DATA*);
	void SetGraphicsDynamicConstantBuffer(uint32_t, size_t, const void*);
	template <typename T> void SetGraphicsDynamicConstantBuffer(uint32_t rootParameterIndex,
		const T& data) {
		SetGraphicsDynamicConstantBuffer(rootParameterIndex, sizeof(T), &data);
	}
	void SetGraphics32BitConstants(uint32_t, size_t, const void*);
	template <typename T> void SetGraphics32BitConstants(uint32_t rootParameterIndex,
		const T& constants) {
		static_assert(sizeof(T) % sizeof(uint32_t) == 0, "Size of type must be a multiple of 4 bytes");
		SetGraphics32BitConstants(rootParameterIndex, sizeof(T) / sizeof(uint32_t), &constants);
	}
	void SetCompute32BitConstants(uint32_t, size_t, const void*);
	template <typename T> void SetCompute32BitConstants(uint32_t rootParameterIndex,
		const T& constants) {
		static_assert(sizeof(T) % sizeof(uint32_t) == 0, "Size of type must be a multiple of 4 bytes");
		SetCompute32BitConstants(rootParameterIndex, sizeof(T) / sizeof(uint32_t), &constants);
	}
	void SetVertexBuffer(uint32_t, const VertexBuffer&);
	void SetDynamicVertexBuffer(uint32_t, size_t, size_t, const void*);
	template <typename T> void SetDynamicVertexBuffer(uint32_t slot, 
		const std::vector<T> vertexBufferData) {
		SetDynamicVertexBuffer(slot, vertexBufferData.size(), sizeof(T), vertexBufferData.data());
	}
	void SetIndexBuffer(const IndexBuffer&);
	void SetDynamicIndexBuffer(size_t, DXGI_FORMAT, const void*);
	template <typename T> void SetDynamicIndexBuffer(const std::vector<T>& indexBufferData) {
		static_assert(sizeof(T) == 2 || sizeof(T) == 4);
		DXGI_FORMAT indexFormat = (sizeof(T) == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
		SetDynamicIndexBuffer(indexBufferData.size(), indexFormat, indexBufferData.data());
	}
	void SetGraphicsDynamicStructuredBuffer(uint32_t, size_t, size_t, const void*);
	template <typename T> void SetGraphicsDynamicStructuredBuffer(uint32_t slot, 
		const std::vector<T>& bufferData) {
		SetGraphicsDynamicStructuredBuffer(slot, bufferData.size(), sizeof(T), bufferData.data());
	}
	void SetViewport(const D3D12_VIEWPORT&);
	void SetViewports(const std::vector<D3D12_VIEWPORT>&);
	void SetScissorRect(const D3D12_RECT&);
	void SetScissorRects(const std::vector<D3D12_RECT>&);
	void SetPipelineState(Microsoft::WRL::ComPtr<ID3D12PipelineState>);
	void SetGraphicsRootSignature(const RootSignature&);
	void SetComputeRootSignature(const RootSignature&);
	void SetShaderResourceView(uint32_t, uint32_t, const Resource&, 
		D3D12_RESOURCE_STATES = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE | 
		D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, uint32_t = 0, 
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, 
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr);
	void SetUnorderedAccessView(uint32_t, uint32_t, const Resource&,
		D3D12_RESOURCE_STATES = D3D12_RESOURCE_STATE_UNORDERED_ACCESS, uint32_t = 0,
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES,
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr);
	void SetRenderTarget(const RenderTarget&);
	void Draw(uint32_t, uint32_t = 1, uint32_t = 0, uint32_t = 0);
	void DrawIndexed(uint32_t, uint32_t = 1, uint32_t = 0, int32_t = 0, uint32_t = 0);
	void Dispatch(uint32_t, uint32_t = 0, uint32_t = 1);
	bool Close(CommandList&);
	void Close();
	void Reset();
	void ReleaseTrackedObjects();
	void SetDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE, ID3D12DescriptorHeap*);
	std::shared_ptr<CommandList> GetGenerateMipsCommandList() const { return _ComputeCommandList; }

private:
	void TrackResource(Microsoft::WRL::ComPtr<ID3D12Object>);
	void TrackResource(const Resource&);
	void GenerateMipsUAV(Texture&, DXGI_FORMAT);
	void CopyBuffer(Buffer&, size_t, size_t, const void*, 
		D3D12_RESOURCE_FLAGS = D3D12_RESOURCE_FLAG_NONE);
	void BindDescriptorHeaps();
	using TrackedObjects = std::vector<Microsoft::WRL::ComPtr<ID3D12Object> >;
	D3D12_COMMAND_LIST_TYPE								_D3D12CommandListType;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList2>	_D3D12CommandList;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>		_D3D12CommandAllocator;
	std::shared_ptr<CommandList>						_ComputeCommandList;
	ID3D12RootSignature*								_RootSignature;
	std::unique_ptr<UploadBuffer>						_UploadBuffer;
	std::unique_ptr<ResourceStateTracker>				_ResourceStateTracker;
	std::unique_ptr<DynamicDescriptorHeap> 
		_DynamicDescriptorHeap[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	ID3D12DescriptorHeap* _DescriptorHeaps[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
	std::unique_ptr<GenerateMipsPSO>					_GenerateMipsPSO;
	std::unique_ptr<PanoToCubemapPSO>					_PanoToCubemapPSO;
	TrackedObjects										_TrackedObjects;
	static std::map<std::wstring, ID3D12Resource*>		_TextureCache;
	static std::mutex									_TextureCacheMutex;
};