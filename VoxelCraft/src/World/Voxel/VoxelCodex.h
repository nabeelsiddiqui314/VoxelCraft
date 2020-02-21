#pragma once
#include "VoxelData.h"
#include <array>

namespace Voxel {
	class Codex
	{
	private:
		Codex();
	public:
		static Codex& getInstance();
	public:
		const Data& getVoxelData(Type id);
	private:
		std::size_t index(Type voxel);
	private:
		std::array<Data, static_cast<std::size_t>(Type::COUNT)> s_voxels;
	};
}