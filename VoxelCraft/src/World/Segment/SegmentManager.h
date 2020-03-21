#pragma once
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <utility>
#include "RenderableSegment.h"
#include "Generation/SegmentGenerator.h"

class SegmentManager
{
private:
	typedef std::unordered_map<Vector3, RenderableSegment> SegmentHashMap;
public:
	SegmentManager() = default;
	~SegmentManager();
public:
	void loadSegment(const Vector3& pos);
	void unloadSegment(const std::function<bool(const Vector3& pos)>& cond);

	void addSegment(const Vector3& pos, Segment& segment); // these will get called by ItaskProducts
	void addMesh(const Vector3& pos, const SegmentMeshes& meshes);

	bool doesSegmentExist(const Vector3& pos) const;

	void loadGeneratedSegments();

	void render(MasterRenderer& renderer, const Frustum& frustum);
private:
	SegmentHashMap m_segments;
	SegmentGenerator m_segmentGenerator;
};

