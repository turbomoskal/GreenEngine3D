#pragma once

#include <d3dx12.h>

#include <wrl.h>

#include <vector>
#include <array>

class RootSignature {
public:
	RootSignature();
	RootSignature(const D3D12_ROOT_SIGNATURE_DESC1&, D3D_ROOT_SIGNATURE_VERSION);
	virtual ~RootSignature();
	void Destroy();
	Microsoft::WRL::ComPtr<ID3D12RootSignature> GetRootSignature() const { return _RootSignature; }
	void SetRootSignatureDesc(const D3D12_ROOT_SIGNATURE_DESC1&, D3D_ROOT_SIGNATURE_VERSION);
	const D3D12_ROOT_SIGNATURE_DESC1& GetRootSignatureDesc() const { return _RootSignatureDesc; }
	uint32_t GetDescriptorTableBitMask(D3D12_DESCRIPTOR_HEAP_TYPE) const;
	uint32_t GetNumDescriptors(uint32_t) const;

private:
	D3D12_ROOT_SIGNATURE_DESC1						_RootSignatureDesc;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>		_RootSignature;
	std::array<uint32_t, 32>						_NumDescriptorsPerTable{};
	uint32_t										_SamplerTableBitMask;
	uint32_t										_DescriptorTableBitMask;
};