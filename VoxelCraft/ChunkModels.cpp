#include "stdafx.h"
#include "ChunkModels.h"

void ChunkModels::createMesh(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk, const ChunkBlocks& cFront,
	const ChunkBlocks& cBack, const ChunkBlocks& cLeft, const ChunkBlocks& cRight) {
	m_model.addMesh(m_meshGenerator.generateMesh(originX, originZ, chunk, cFront, cBack, cLeft, cRight));
}

void ChunkModels::cleanUp() {
	m_meshGenerator.cleanUp();
}

const Model& ChunkModels::getModel() const {
	return m_model;
}
