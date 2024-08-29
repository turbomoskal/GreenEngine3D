#pragma once

#include "CommandList.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

#include <memory>
#include <vector>

struct VertexPositionNormalTexture {
	VertexPositionNormalTexture() = default;
	VertexPositionNormalTexture(const DirectX::XMFLOAT3& position,
		const DirectX::XMFLOAT3& normal, const DirectX::XMFLOAT2& textureCoordinate) :
		_Position(position),
		_Normal(normal),
		_TextureCoordinate(textureCoordinate) {}
	VertexPositionNormalTexture(DirectX::FXMVECTOR position,
		DirectX::FXMVECTOR normal, DirectX::FXMVECTOR textureCoordinate) {
		XMStoreFloat3(&this->_Position, position);
		XMStoreFloat3(&this->_Normal, normal);
		XMStoreFloat2(&this->_TextureCoordinate, textureCoordinate);
	}
	DirectX::XMFLOAT3						_Position;
	DirectX::XMFLOAT3						_Normal;
	DirectX::XMFLOAT2						_TextureCoordinate;
	static const int						InputElementCount = 3;
	static const D3D12_INPUT_ELEMENT_DESC	InputElements[InputElementCount];
};

using VertexCollection = std::vector<VertexPositionNormalTexture>;
using IndexCollection = std::vector<uint16_t>;

class Mesh {
public:
	void Draw(CommandList&);
	static std::unique_ptr<Mesh> CreateCube(CommandList&, float = 1, bool = false);
	static std::unique_ptr<Mesh> CreateSphere(CommandList&, float = 1, size_t = 16, bool = false);
	static std::unique_ptr<Mesh> CreateCone(CommandList&, float = 1, float = 1, size_t = 32, bool = false);
	static std::unique_ptr<Mesh> CreateTorus(CommandList&, float = 1, float = 0.333f, size_t = 32, bool = false);
	static std::unique_ptr<Mesh> CreatePlane(CommandList&, float = 1, float = 1, bool = false);

private:
	friend struct std::default_delete<Mesh>;
	Mesh();
	Mesh(const Mesh&) = delete;
	virtual ~Mesh();
	void Initialize(CommandList&, VertexCollection&, IndexCollection&, bool);
	VertexBuffer	_VertexBuffer;
	IndexBuffer		_IndexBuffer;
	uint32_t		_IndexCount;
};