#include "SegmentGenerator.h"
#include "../SegmentManager.h"

SegmentGenerator::SegmentGenerator() {
	for (int i = 0; i < 1; i++) {
		m_threadPool.emplace_back([&]() {generationThread(); });
	}
}

void SegmentGenerator::recieveProducedData(SegmentManager& manager) {
	std::shared_ptr<ITaskProduct> product;
	if (m_productQueue.tryPop(product)) {
		product->sendProduct(manager);
	}
}

void SegmentGenerator::generationThread() {
	while (m_isRunning) {
		std::shared_ptr<IConcurrentTask> task;
		m_taskQueue.pop(task);

		task->execute();

		m_productQueue.push(task->getProduct());
	}
}

SegmentGenerator::~SegmentGenerator() {
	m_isRunning = false;

	for (auto& thread : m_threadPool) {
		thread.join();
	}
}