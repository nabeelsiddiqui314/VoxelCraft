#pragma once
#include <queue>
#include <mutex>

template <typename T, std::size_t Capacity>
class Blocking_Queue {
public:
	void pop(T& popped_data) {
		std::unique_lock<std::mutex> lock(m_mutex);

		while (m_queue.empty()) {
			m_consumers.wait(lock);
		}

		popped_data = m_queue.front();
		m_queue.pop();
	}

	void push(const T& data) {
		std::unique_lock<std::mutex> lock(m_mutex);

		m_queue.push(data);

		lock.unlock();
		m_consumers.notify_one();
	}
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_consumers;
};