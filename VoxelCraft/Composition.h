#pragma once
#include <vector>
#include "BlockTypes.h"

class Composition
{
public:
	typedef std::pair<BlockType, int> Layer;
public:
	Composition(const std::vector<Layer>& layers);
	~Composition() = default;
public:
	BlockType getBlockAt(int depth) const;
private:
	std::vector<Layer> m_layers;
};

