#pragma once
#include <memory>
#include "SegmentModel.h"
#include "../../Math/AABB.h"
#include "../../Math/vector3.h"

class Segment;
class MasterRenderer;
class Frustum;

class RenderableSegment {
public:
	RenderableSegment(std::shared_ptr<Segment> segment, const Vector3& worldPos);
	~RenderableSegment();
public:
	void generateMesh();
	void render(MasterRenderer& renderer, const Frustum& frustum);
	void cleanUp();

	std::shared_ptr<Segment> getSegment() const;
private:
	void deleteBuffers();
private:
	std::shared_ptr<Segment> m_segment;
	Vector3 m_worldPos;
	MeshTypes m_meshTypes;
	AABB m_box;

	bool m_hasMeshGenerated = false;
	bool m_hasLoadedModel = false;
};