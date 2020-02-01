#pragma once
#include <queue>
#include <mutex>

template <typename T>
class Safe_Queue {
public:
	T pop() {
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_queue.empty()) {
			m_blocker.wait(lock);
		}

		auto data = m_queue.front();
		m_queue.pop();
		return data;
	}

	void push(const T& data) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(data);
		lock.unlock();
		m_blocker.notify_one();
	}
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_blocker;
};