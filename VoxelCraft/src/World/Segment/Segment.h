#pragma once
#include <array>
#include "../Voxel/VoxelCodex.h"
#include "../Voxel/VoxelElement.h"
#include "../../Math/AABB.h"
#include "../../Math/vector3.h"
#include "LightingComputer.h"
#include "SegmentModel.h"

struct VecXZ;
class MasterRenderer;
class SectorManager;

class Segment
{
public:
	Segment(int x, int y, int z, SectorManager& sectors);
public:
	void setNaturalLight(int x, int y, int z, int luminocity);

	void setVoxel(std::int16_t x, std::int16_t y, std::int16_t z, Voxel::Type id);
	Voxel::Element getVoxel(std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh();
	Segment* getRelativeSegment(int x, int y, int z);
	const Segment* getRelativeSegment(int x, int y, int z) const;
	const Vector3& getWorldPosition() const;

	void regenMesh();
	void loadModel();
	void cleanUp();
	void cleanBuffers();

	void render(MasterRenderer& renderer);

	void setBoxPosition(const glm::vec3& pos);
	const AABB& getBox() const;

	bool isAllOpaque() const;
	bool isEmpty() const;
	bool hasMeshGenerated() const;
	bool hasModelLoaded() const;
public:
	static constexpr std::int16_t WIDTH = 16;
private:
	bool isInBounds(int x, int y, int z) const;
private: 
	std::array<Voxel::Element, WIDTH * WIDTH * WIDTH> m_voxels;
	std::int16_t m_opaqueCount;
	std::int16_t m_voidCount;

	AABB m_box;

	SectorManager& m_sectors;
	Vector3 m_worldPosition;
	LightingComputer m_lightcomputer;

	MeshTypes m_meshTypes;
	bool m_hasMeshGenerated = false;
	bool m_hasLoadedModel = false;
};

