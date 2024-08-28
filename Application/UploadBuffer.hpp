#pragma once

#include "Defines.h"

#include <wrl.h>
#include <d3d12.h>

#include <memory>
#include <deque>

class UploadBuffer {
public:
	struct Allocation {
		void*						CPU;
		D3D12_GPU_VIRTUAL_ADDRESS	GPU;
	};
	explicit UploadBuffer(size_t = _2MB);
	virtual ~UploadBuffer();
	size_t GetPageSize() const { return _PageSize; }
	Allocation Allocate(size_t, size_t);
	void Reset();
private:
	struct Page {
		Page(size_t);
		~Page();
		bool HasSpace(size_t, size_t) const;
		Allocation Allocate(size_t, size_t);
		void Reset();
	private:
		Microsoft::WRL::ComPtr<ID3D12Resource>	_D3D12Resource;
		void*									_CPUPtr;
		D3D12_GPU_VIRTUAL_ADDRESS				_GPUPtr;
		size_t									_PageSize;
		size_t									_Offset;
	};
	using PagePool = std::deque<std::shared_ptr<Page> >;
	std::shared_ptr<Page> RequestPage();
	PagePool				_PagePool;
	PagePool				_AvailablePages;
	std::shared_ptr<Page>	_CurrentPage;
	size_t					_PageSize;
};