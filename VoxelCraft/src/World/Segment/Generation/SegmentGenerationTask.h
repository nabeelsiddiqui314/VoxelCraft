#pragma once
#include "IConcurrentTask.h"
#include "../../../Math/vector3.h"
#include "../Segment.h"

class SegmentGenerationTask : public IConcurrentTask
{
public:
	SegmentGenerationTask(const Vector3& pos);
	~SegmentGenerationTask() {};
public:
	void execute() override;
	std::shared_ptr<ITaskProduct> getProduct() override;
private:
	Vector3 m_position;
	Segment m_segment;
};

class SegmentProduct : public ITaskProduct{
private:
	Segment& m_segment;
public:
	SegmentProduct(Segment& segment);
	~SegmentProduct() {};
public:
	void sendProduct(SegmentManager& manager) override;
};