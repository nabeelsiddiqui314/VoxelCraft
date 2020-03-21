#pragma once
#include "Segment.h"
#include "SegmentModels.h"
#include "../../Math/AABB.h"

class MasterRenderer;
class Frustum;

struct RenderableSegment {
	Segment segment;
public:
	RenderableSegment(Segment& segment);
public:
	void loadMeshes(const SegmentMeshes& meshes);
	void loadModels();
	void remesh();
	void cleanUp();
	bool hasMeshGenerated();

	void render(MasterRenderer& renderer, const Frustum& frustum);
private:
	void cleanUpMeshes();
	void cleanUpModels();
private:
	SegmentMeshes m_meshes;
	SegmentModels m_models;

	bool m_hasMeshGenerated = false;
	bool m_hasModelLoaded = false;
	
	AABB m_boundingBox;
};