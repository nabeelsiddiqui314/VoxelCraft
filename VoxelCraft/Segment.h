#pragma once
#include <array>
#include "BlockTypes.h"
#include "BlockCodex.h"
#include "SegmentMeshMaker.h"
#include "MasterRenderer.h"
#include "SegmentModel.h"

class Segment
{
public:
	Segment();
public:
	void setBlock(std::int16_t x, std::int16_t y, std::int16_t z, BlockType id);
	BlockType getBlock(std::int16_t x, std::int16_t y, std::int16_t z) const;

	void makeMesh(std::int16_t originX, std::int16_t originY, std::int16_t originZ,
		const Segment* sector,
		const Segment* top, const Segment* bottom,
		const Segment* left, const Segment* right,
		const Segment* front, const Segment* back);
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
	std::array<BlockType, WIDTH * WIDTH * WIDTH> m_blocks;
	std::int16_t m_opaqueCount;
	std::int16_t m_voidCount;

	AABB m_box;

	MeshTypes m_meshTypes;
	bool m_hasMeshGenerated = false;
	bool m_hasLoadedModel = false;
};

