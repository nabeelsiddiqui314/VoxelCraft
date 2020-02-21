#pragma once
#include <vector>
#include "../../Voxel/VoxelEnums.h"

class Composition
{
public:
	typedef std::pair<Voxel::Type, int> Layer;
public:
	Composition(const std::vector<Layer>& layers);
	~Composition() = default;
public:
	Voxel::Type getVoxelAt(int depth) const;
private:
	std::vector<Layer> m_layers;
};

