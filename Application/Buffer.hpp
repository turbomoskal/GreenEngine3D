#pragma once

#include "Resource.hpp"

class Buffer : public Resource {
public:
	explicit Buffer(const std::wstring & = L"");
	explicit Buffer(const D3D12_RESOURCE_DESC&, size_t, size_t, const std::wstring & = L"");
	virtual void CreateViews(size_t, size_t) = 0;
};