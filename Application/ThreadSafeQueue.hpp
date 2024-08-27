#pragma once
#include <queue>
#include <mutex>

template <typename T> class ThreadSafeQueue {
public:
	ThreadSafeQueue();
	ThreadSafeQueue(const ThreadSafeQueue&);
	void Push(T);
	bool TryPop(T&);
	bool Empty() const;
	size_t Size() const;

private:
	std::queue<t> _Queue;
	mutable std::mutex _Mutex;
};