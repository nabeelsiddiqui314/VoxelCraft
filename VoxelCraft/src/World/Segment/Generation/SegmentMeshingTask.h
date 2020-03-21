#pragma once
#include "IConcurrentTask.h"
#include "../Segment.h"
#include "../SegmentModels.h"

class SegmentMeshingTask : public IConcurrentTask
{
public:
	SegmentMeshingTask(const Segment& segment);
	~SegmentMeshingTask() {}
public:
	void execute() override;
	std::shared_ptr<ITaskProduct> getProduct() override;
private:
	const Segment& m_segment;
	SegmentMeshes m_meshes;
};

class MeshProduct : public ITaskProduct {
private:
	const Segment& m_segment;
	const SegmentMeshes& m_meshes;
public:
	MeshProduct(const Segment& segment, const SegmentMeshes& meshes);
	~MeshProduct() {};
public:
	void sendProduct(SegmentManager& manager) override;
};