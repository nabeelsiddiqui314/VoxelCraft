#include "stdafx.h"
#include "VoxelCodex.h"

#include "NonUpdatable.h"
#include "GroundFloraHandler.h"
#include "LiquidHandler.h"
#include "GravityHandler.h"

namespace Voxel {
	std::array<Data, static_cast<std::size_t>(Type::COUNT)> Codex::s_voxels;

	void Codex::init() {
		s_voxels[index(Type::VOID)]  = Data();
		s_voxels[index(Type::GRASS)] = Data(std::make_unique<NonUpdatable>(),       {0, 1, 2, Shape::CUBE, ShaderType::SOLID, true   });
		s_voxels[index(Type::DIRT)]  = Data(std::make_unique<NonUpdatable>(),       {2, 2, 2, Shape::CUBE, ShaderType::SOLID, true   });
		s_voxels[index(Type::STONE)] = Data(std::make_unique<NonUpdatable>(),       {3, 3, 3, Shape::CUBE, ShaderType::SOLID, true   });
		s_voxels[index(Type::SAND)]  = Data(std::make_unique<GravityHandler>(),     {4, 4, 4, Shape::CUBE, ShaderType::SOLID, true   });
		s_voxels[index(Type::WATER)] = Data(std::make_unique<LiquidHandler>(),      {5, 5, 5, Shape::BLOB, ShaderType::LIQUID, false });
		s_voxels[index(Type::ROSE)]  = Data(std::make_unique<GroundFloraHandler>(), {6, 6, 6, Shape::CROSS, ShaderType::FLORA, false });
		s_voxels[index(Type::SHRUB)] = Data(std::make_unique<GroundFloraHandler>(), {7, 7, 7, Shape::CROSS, ShaderType::FLORA, false });
	}

	const Data& Codex::getVoxelData(Type id) {
		return s_voxels[static_cast<std::size_t>(id)];
	}

	std::size_t Codex::index(Type voxel) {
		return static_cast<std::size_t>(voxel);
	}
}