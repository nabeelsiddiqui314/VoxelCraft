#pragma once
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <utility>
#include "../../Math/Vector3.h"
#include "RenderableSegment.h"

class Segment;
class RenderableSegment;
class MasterRenderer;
class Frustum;

class SegmentManager
{
private:
	typedef std::function<bool(const Vector3&)> RemovalTest;
public:
	SegmentManager() = default;
	~SegmentManager();
public:
	void loadSegment(const Vector3& pos, std::shared_ptr<Segment> segment);
	void unloadSegmentIf(const RemovalTest& callback);

	bool doesSegmentExist(const Vector3& pos) const;

	void makeMesh(const Vector3& pos);

	void renderSegments(MasterRenderer& renderer, const Frustum& frustum);
private:
	std::unordered_map<Vector3, RenderableSegment> m_segments;
};

