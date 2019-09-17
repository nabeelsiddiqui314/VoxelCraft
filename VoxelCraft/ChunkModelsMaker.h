#pragma once
#include "Model.h"
#include "MeshGenerator.h"
#include "ChunkBlocks.h"
#include "BlockCodex.h"
#include <optional>

struct PartialModel {
	std::optional<Model> model;
	MeshGenerator meshMaker;
};

struct ChunkModels {
	PartialModel solid;
};

class ChunkModelsMaker
{
public:
	ChunkModelsMaker();
public:
	void generateMeshes(std::int16_t originX, std::int16_t originZ, const ChunkBlocks& chunk,
		const ChunkBlocks& cFront, const ChunkBlocks& cBack, const ChunkBlocks& cLeft,
		const ChunkBlocks& cRight);
	void addMeshesToModels();
	const ChunkModels& getModels() const;
private:
	void prepareModel(PartialModel& pModel);
	void cleanUp();
private:
	static const std::array<GLfloat, 12> s_front;
	static const std::array<GLfloat, 12> s_back;
	static const std::array<GLfloat, 12> s_right;
	static const std::array<GLfloat, 12> s_left;
	static const std::array<GLfloat, 12> s_top;
	static const std::array<GLfloat, 12> s_bottom;

	ChunkModels m_models;
};

