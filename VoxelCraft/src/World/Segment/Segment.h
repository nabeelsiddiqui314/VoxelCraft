#pragma once
#include <array>
#include "../Voxel/VoxelCodex.h"
#include "../Voxel/VoxelElement.h"
#include "LightingComputer.h"

class Segment
{
public:
	enum class NeighborPosition {
		TOP,
		BOTTTOM,
		LEFT,
		RIGHT,
		FRONT,
		BACK
	};
public:
	Segment();
public:
	void setNaturalLight(int x, int y, int z, int luminocity);

	void setVoxel(int x, int y, int z, Voxel::Type id);
	Voxel::Element getVoxel(int x, int y, int z) const;
	Voxel::Element getVoxelFromNeighborhood(int x, int y, int z) const;

	void setNeighbor(std::shared_ptr<Segment> neighbor, const NeighborPosition& pos);
	std::shared_ptr<Segment> getNeighbor(const NeighborPosition& pos) const;

	bool isAllOpaque() const;
	bool isEmpty() const;
public:
	static constexpr std::int16_t WIDTH = 16;
private:
	bool isInBounds(int x, int y, int z) const;
private: 
	std::array<Voxel::Element, WIDTH * WIDTH * WIDTH> m_voxels;
	std::int16_t m_opaqueCount;
	std::int16_t m_voidCount;

	std::array<std::weak_ptr<Segment>, 6> m_neighbors;

	LightingComputer m_lightcomputer;
};

