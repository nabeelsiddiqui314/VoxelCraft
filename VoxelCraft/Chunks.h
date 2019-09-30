#pragma once
#include "SegmentMeshMaker.h"
#include "Segment.h"

class Chunks
{
public:
	void setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh(std::int16_t x, std::int16_t z,
		const Chunks* left, const Chunks* right,
		const Chunks* front, const Chunks* back);
	void regenMesh(std::int16_t y);
	void cleanUp();

	const Segment& getSegment(std::uint8_t index) const;
	void render(MasterRenderer& renderer);
public:
	static constexpr std::int16_t HEIGHT = 16;
private:
	std::array<Segment, HEIGHT> m_segments;
};

