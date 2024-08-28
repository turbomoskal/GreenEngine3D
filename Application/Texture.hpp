#pragma once

#include "Resource.hpp"
#include "DescriptorAllocation.hpp"
#include "TextureUsage.hpp"

#include <d3dx12.h>

#include <mutex>
#include <unordered_map>

class Texture : public Resource {
public:
	explicit Texture(TextureUsage = TextureUsage::Albedo, const std::wstring & = L"");
	explicit Texture(const D3D12_RESOURCE_DESC&, const D3D12_CLEAR_VALUE* = nullptr, 
		TextureUsage = TextureUsage::Albedo, const std::wstring & = L"");
	explicit Texture(Microsoft::WRL::ComPtr<ID3D12Resource>, 
		TextureUsage = TextureUsage::Albedo, const std::wstring & = L"");
	Texture(const Texture&);
	Texture(Texture&&);
	Texture& operator=(const Texture&);
	Texture& operator=(Texture&&);
	virtual ~Texture();
	TextureUsage GetTextureUsage() const { return _TextureUsage; }
	void SetTextureUsage(TextureUsage usage) { _TextureUsage = usage; }
	void Resize(uint32_t, uint32_t, uint32_t = 1);
	virtual void CreateViews();
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const override;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetRenderTargetView() const;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView() const;
	bool CheckSRVSupport() { return CheckFormatSupport(D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE); }
	bool CheckRTVSupport() { return CheckFormatSupport(D3D12_FORMAT_SUPPORT1_RENDER_TARGET); }
	bool CheckUAVSupport() {
		return CheckFormatSupport(D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW) &&
			CheckFormatSupport(D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD) &&
			CheckFormatSupport(D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE);
	}
	bool CheckDSVSupport() { return CheckFormatSupport(D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL); }
	static bool IsUAVCompatibleFormat(DXGI_FORMAT);
	static bool IsSRGBFormat(DXGI_FORMAT);
	static bool IsBGRFormat(DXGI_FORMAT);
	static bool IsDepthFormat(DXGI_FORMAT);
	static DXGI_FORMAT GetTypelessFormat(DXGI_FORMAT);
	static DXGI_FORMAT GetUAVCompatibleFormat(DXGI_FORMAT);

private:
	DescriptorAllocation CreateShaderResourceView(const D3D12_SHADER_RESOURCE_VIEW_DESC*) const;
	DescriptorAllocation CreateUnorderedAccessView(const D3D12_UNORDERED_ACCESS_VIEW_DESC*) const;
	mutable std::unordered_map<size_t, DescriptorAllocation>	_ShaderResourceViews;
	mutable std::unordered_map<size_t, DescriptorAllocation>	_UnorderedAccessViews;
	mutable std::mutex											_ShaderResourceViewsMutex;
	mutable std::mutex											_UnorderedAccessViewsMutex;
	DescriptorAllocation										_RenderTargetView;
	DescriptorAllocation										_DepthStencilView;
	TextureUsage												_TextureUsage;
};