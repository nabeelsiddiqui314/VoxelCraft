#pragma once
#include <memory>
#include "../../../CppUtil/Blocking_Queue.h"
#include "IConcurrentTask.h"

class SegmentGenerator
{
public:
	SegmentGenerator();
	~SegmentGenerator();
public:
	template <typename T, typename... Args>
	void orderTask(Args&&... args) {
		m_taskQueue.push(std::make_shared<T>(std::forward<Args>(args)...));
	}

	void recieveProducedData(SegmentManager& manager);
private:
	void generationThread();
private:
	std::vector<std::thread> m_threadPool;
	bool m_isRunning = true;

	Blocking_Queue<std::shared_ptr<IConcurrentTask>> m_taskQueue;
	Blocking_Queue<std::shared_ptr<ITaskProduct>> m_productQueue;
};

