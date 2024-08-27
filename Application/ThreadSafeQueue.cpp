#include "ThreadSafeQueue.hpp"

template <typename T> ThreadSafeQueue<T>::ThreadSafeQueue() = default;
template <typename T> ThreadSafeQueue<T>::ThreadSafeQueue(const ThreadSafeQueue& copy) {
	std::scoped_lock<std::mutex> lock(copy._Mutex);
	_Queue = copy._Queue;
}
template <typename T> void ThreadSafeQueue<T>::Push(T value) {
	std::scoped_lock<std::mutex> lock(_Mutex);
	_Queue.push(std::move(value));
}
template <typename T> bool ThreadSafeQueue<T>::TryPop(T& value) {
	std::scoped_lock<std::mutex> lock(_Mutex);
	if (_Queue.empty()) return false;
	value = _Queue.front();
	_Queue.pop();
	return true;
}
template <typename T> bool ThreadSafeQueue<T>::Empty() const {
	std::scoped_lock<std::mutex> lock(_Mutex);
	return _Queue.empty();
}
template <typename T> size_t ThreadSafeQueue<T>::Size() const {
	std::scoped_lock<std::mutex> lock(_Mutex);
	return _Queue.size();
}