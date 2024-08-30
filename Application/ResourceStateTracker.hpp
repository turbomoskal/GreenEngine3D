#pragma once

#include <d3d12.h>

#include <mutex>
#include <map>
#include <unordered_map>
#include <vector>

class CommandList;
class Resource;

class ResourceStateTracker {
public:
	ResourceStateTracker();
	virtual ~ResourceStateTracker();
	void ResourceBarrier(const D3D12_RESOURCE_BARRIER&);
	void TransitionResource(ID3D12Resource*, D3D12_RESOURCE_STATES, 
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
	void TransitionResource(const Resource&, D3D12_RESOURCE_STATES,
		uint32_t = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES);
	void UAVBarrier(const Resource* = nullptr);
	void AliasBarrier(const Resource* = nullptr, const Resource* = nullptr);
	uint32_t FlushPendingResourceBarriers(CommandList&);
	void FlushResourceBarriers(CommandList&);
	void CommitFinalResourceStates();
	void Reset();
	static void Lock();
	static void Unlock();
	static void AddGlobalResourceState(ID3D12Resource*, D3D12_RESOURCE_STATES);
	static void RemoveGlobalResourceState(ID3D12Resource*);

private:
	using ResourceBarriers = std::vector<D3D12_RESOURCE_BARRIER>;
	ResourceBarriers _PendingResourceBarriers;
	ResourceBarriers _ResourceBarriers;
	struct ResourceState {
		explicit ResourceState(D3D12_RESOURCE_STATES s = D3D12_RESOURCE_STATE_COMMON) :
			State(s){}
		void SetSubresourceState(uint32_t sub, D3D12_RESOURCE_STATES state) {
			if (sub == D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES) {
				State = state;
				SubresourceState.clear();
			}
			else SubresourceState[sub] = state;
		}
		D3D12_RESOURCE_STATES GetSubresourceState(uint32_t sub) const {
			D3D12_RESOURCE_STATES state = State;
			const auto i = SubresourceState.find(sub);
			if (i != SubresourceState.end()) state = i->second;
			return state;
		}
		D3D12_RESOURCE_STATES						State;
		std::map<uint32_t, D3D12_RESOURCE_STATES>	SubresourceStates;
	};
	using ResourceStateMap = std::unordered_map<ID3D12Resource*, ResourceState>;
	ResourceStateMap			_FinalResourceState;
	static ResourceStateMap		_GlobalResourcesState;
	static std::mutex			_GlobalMutex;
	static bool					_IsLocked;
};