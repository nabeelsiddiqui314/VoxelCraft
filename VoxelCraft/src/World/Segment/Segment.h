#pragma once
#include <array>
#include "../Voxel/VoxelCodex.h"
#include "../Voxel/VoxelElement.h"
#include "../../Math/vector3.h"
#include "LightingComputer.h"

class Segment
{
private:
	struct NeighborPosition {
		int x, y, z;
		Segment* parent;
	};
public:
	enum class Neighbor : std::uint8_t {
		TOP = 0, 
		BOTTOM,
		LEFT, 
		RIGHT,
		FRONT, 
		BACK
	};
public:
	Segment(int x, int y, int z);
public:
	void setNaturalLight(int x, int y, int z, int luminocity);

	void setVoxel(int x, int y, int z, Voxel::Type id);
	Voxel::Element getVoxel(int x, int y, int z) const;

	const Vector3& getWorldPosition() const;
	void setNeighborSegment(const Neighbor& neighborPos, Segment* segment);
	const Segment* getNeighborSegment(const Neighbor& neighborPos) const;

	bool isAllOpaque() const;
	bool isEmpty() const;
public:
	static constexpr std::int16_t WIDTH = 16;
private:
	bool isInBounds(int x, int y, int z) const;
	std::uint8_t neighbor(const Neighbor& neighbor) const;

	NeighborPosition getNeighborPosition(int x, int y, int z) const;
private: 
	std::array<Voxel::Element, WIDTH * WIDTH * WIDTH> m_voxels;
	std::array<Segment*, 6> m_neighbors;
	std::int16_t m_opaqueCount;
	std::int16_t m_voidCount;
	
	Vector3 m_worldPosition;
	LightingComputer m_lightcomputer;
};

