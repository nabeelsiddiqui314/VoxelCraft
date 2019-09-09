#include "stdafx.h"
#include "ChunkModelsMaker.h"

// indices in 0, 1, 2, 0, 2, 3

const std::array<GLfloat, 12> ChunkModelsMaker::s_front = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0
};

const std::array<GLfloat, 12> ChunkModelsMaker::s_back = {
	1, 0, -1,
	0, 0, -1,
	0, 1, -1,
	1, 1, -1
};

const std::array<GLfloat, 12> ChunkModelsMaker::s_left = {
	0, 0, -1,
	0, 0,  0,
	0, 1,  0,
	0, 1, -1
};

const std::array<GLfloat, 12> ChunkModelsMaker::s_right = {
	1, 0,  0,
	1, 0, -1,
	1, 1, -1,
	1, 1,  0
};

const std::array<GLfloat, 12> ChunkModelsMaker::s_top = {
	0, 1,  0,
	1, 1,  0,
	1, 1, -1,
	0, 1, -1
};

const std::array<GLfloat, 12> ChunkModelsMaker::s_bottom = {
	0, 0, -1,
	1, 0, -1,
	1, 0,  0,
	0, 0,  0
};

void ChunkModelsMaker::generateModels(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk, const ChunkBlocks& cFront, const ChunkBlocks& cBack, const ChunkBlocks& cLeft, const ChunkBlocks& cRight) {
	BlockType top
		, bottom
		, left
		, right
		, front
		, back;

	auto setNeighbors = [&](std::int16_t x, std::int16_t y, std::int16_t z) {
		// x
		if (x - 1 < 0)
			left = cLeft.getBlock(CHUNK_WIDTH - 1, y, z);
		else
			left = chunk.getBlock(x - 1, y, z);

		if (x + 1 >= CHUNK_WIDTH)
			right = cRight.getBlock(0, y, z);
		else
			right = chunk.getBlock(x + 1, y, z);

		//z

		if (z - 1 < 0)
			back = cBack.getBlock(x, y, CHUNK_WIDTH - 1);
		else
			back = chunk.getBlock(x, y, z - 1);

		if (z + 1 >= CHUNK_WIDTH)
			front = cFront.getBlock(x, y, 0);
		else
			front = chunk.getBlock(x, y, z + 1);

		// y
		if (y - 1 < 0)
			bottom = BlockType::VOID;
		else
			bottom = chunk.getBlock(x, y - 1, z);

		if (y + 1 >= CHUNK_HEIGHT)
			top = BlockType::VOID;
		else
			top = chunk.getBlock(x, y + 1, z);
	};

	for (std::int16_t x = 0; x < CHUNK_WIDTH; x++) {
		for (std::int16_t y = 0; y < CHUNK_HEIGHT; y++) {
			for (std::int16_t z = 0; z < CHUNK_WIDTH; z++) {
				if (chunk.getBlock(x, y, z) == BlockType::VOID)
					continue;
				setNeighbors(x, y, z);

				std::int16_t oX = x + originX;
				std::int16_t oZ = z + originZ;

				switch (BlockCodex::getBlockData(chunk.getBlock(x, y, z)).category) {
				case BlockCategory::SOLID:
					if (!BlockCodex::getBlockData(top).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordTop, s_top);

					if (!BlockCodex::getBlockData(bottom).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordBottom, s_bottom);

					if (!BlockCodex::getBlockData(left).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordSide, s_left);

					if (!BlockCodex::getBlockData(right).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordSide, s_right);

					if (!BlockCodex::getBlockData(front).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordSide, s_front);

					if (!BlockCodex::getBlockData(back).opaque)
						m_models.solid.meshMaker.addFace(oX, y, oZ, BlockCodex::getBlockData(chunk.getBlock(x, y, z)).texCoordSide, s_back);
					break;
				}
			}
		}
	}
	prepareModel(m_models.solid);
}

const ChunkModels& ChunkModelsMaker::getModels() const {
	return m_models;
}

void ChunkModelsMaker::cleanUp() {
	m_models.solid.meshMaker.cleanUp();
}

void ChunkModelsMaker::prepareModel(PartialModel& pModel) {
	if (!pModel.meshMaker.getMesh().vertices.empty()) {
		pModel.model.emplace();
		pModel.model.value().addMesh(pModel.meshMaker.getMesh());
	}
	else
		pModel.model = std::nullopt;
}