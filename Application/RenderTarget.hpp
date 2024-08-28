#pragma once

#include <DirectXMath.h>

#include <cstdint>
#include <vector>

#include "Texture.hpp"

enum AttachmentPoint {
	Color0,
	Color1,
	Color2,
	Color3,
	Color4,
	Color5,
	Color6,
	Color7,
	DepthStencil,
	NumAttachmentPoints
};

class RenderTarget {
public:
	RenderTarget();
	RenderTarget(const RenderTarget&) = default;
	RenderTarget(RenderTarget&&) = default;
	RenderTarget& operator=(const RenderTarget&) = default;
	RenderTarget& operator=(RenderTarget&&) = default;
	void AttachTexture(AttachmentPoint, const Texture&);
	const Texture& GetTexture(AttachmentPoint) const;
	void Resize(DirectX::XMUINT2);
	void Resize(uint32_t, uint32_t);
	DirectX::XMUINT2 GetSize() const;
	uint32_t GetWidth() const;
	uint32_t GetHeight() const;
	D3D12_VIEWPORT GetViewport(DirectX::XMFLOAT2 = { 1.f, 1.f }, 
		DirectX::XMFLOAT2 = { 0.f, 0.f }, float = 0.f, float = 1.f) const;
	const std::vector<Texture>& GetTextures() const;
	D3D12_RT_FORMAT_ARRAY GetRenderTargetFormats() const;
	DXGI_FORMAT GetDepthStencilFormat() const;

private:
	std::vector<Texture> _Textures;
	DirectX::XMUINT2 _Size;
};