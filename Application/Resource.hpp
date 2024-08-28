#pragma once

#include <d3d12.h>
#include <wrl.h>

#include <string>
#include <memory>

class Resource {
public:
	explicit Resource(const std::wstring & = L"");
	explicit Resource(const D3D12_RESOURCE_DESC&, 
		const D3D12_CLEAR_VALUE* = nullptr, const std::wstring& = L"");
	explicit Resource(Microsoft::WRL::ComPtr<ID3D12Resource>, const std::wstring & = L"");
	Resource(const Resource&);
	Resource(Resource&&);
	Resource& operator=(const Resource&);
	Resource& operator=(Resource&&) noexcept;
	virtual ~Resource();
	bool IsValid() const { return _D3D12Resource != nullptr; }
	Microsoft::WRL::ComPtr<ID3D12Resource> GetD3D12Resource() const { return _D3D12Resource; }
	D3D12_RESOURCE_DESC GetD3D12ResourceDesc() const;
	virtual void SetD3D12Resource(Microsoft::WRL::ComPtr<ID3D12Resource>, 
		const D3D12_CLEAR_VALUE* = nullptr);
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetShaderResourceView(
		const D3D12_SHADER_RESOURCE_VIEW_DESC* = nullptr) const = 0;
	virtual D3D12_CPU_DESCRIPTOR_HANDLE GetUnorderedAccessView(
		const D3D12_UNORDERED_ACCESS_VIEW_DESC* = nullptr) const = 0;
	void SetName(const std::wstring&);
	virtual void Reset();
	bool CheckFormatSupport(D3D12_FORMAT_SUPPORT1) const;
	bool CheckFormatSupport(D3D12_FORMAT_SUPPORT2) const;

protected:
	Microsoft::WRL::ComPtr<ID3D12Resource>	_D3D12Resource;
	D3D12_FEATURE_DATA_FORMAT_SUPPORT		_FormatSupport;
	std::unique_ptr<D3D12_CLEAR_VALUE>		_D3D12ClearValue;
	std::wstring							_ResourceName;

private:
	void CheckFeatureSupport();
};