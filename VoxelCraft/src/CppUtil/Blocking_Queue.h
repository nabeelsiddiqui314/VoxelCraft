#pragma once
#include <queue>
#include <mutex>

template <typename T>
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

	bool tryPop(T& popped_data) {
		std::unique_lock<std::mutex> lock(m_mutex);

		if (!m_queue.empty()) {
			popped_data = m_queue.front();
			m_queue.pop();
			return true;
		}

		return false;
	}

	void push(const T& data) {
		std::unique_lock<std::mutex> lock(m_mutex);

		m_queue.push(data);

		lock.unlock();
		m_consumers.notify_one();
	}

	void push(const T&& data) {
		std::unique_lock<std::mutex> lock(m_mutex);

		m_queue.push(std::move(data));

		lock.unlock();
		m_consumers.notify_one();
	}
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_consumers;
};