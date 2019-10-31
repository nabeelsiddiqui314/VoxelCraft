#pragma once
#include "VoxelData.h"
#include <array>

namespace Voxel {
	class Codex
	{
		Codex() = delete;
	public:
		static void init();
		static const Data& getVoxelData(Type id);
	private:
		static std::size_t index(Type voxel);
	private:
		static std::array<Data, static_cast<std::size_t>(Type::COUNT)> s_voxels;
	};
}