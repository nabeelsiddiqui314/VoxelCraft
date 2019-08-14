#pragma once
#include "MeshGenerator.h"
#include "Model.h"

class ChunkModels
{
public:
	void createMesh(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk, const ChunkBlocks& cFront,
		const ChunkBlocks& cBack, const ChunkBlocks& cLeft, const ChunkBlocks& cRight);
	void cleanUp();
	const Model& getModel() const;
private:
	MeshGenerator m_meshGenerator;
	Model m_model;
};

