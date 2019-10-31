#pragma once
#include <glm/glm.hpp>
#include "VoxelEnums.h"
#include "VoxelUpdateHandler.h"
#include "NonUpdatable.h"
#include <memory>

namespace Voxel {
	struct Info {
		int texTop;
		int texSide;
		int texBottom;

		Shape shape;
		ShaderType shaderType;
		bool opaque;

		Info()
		  : texTop(0),
			texSide(0),
			texBottom(0),
			shape(Shape::CUBE),
			shaderType(ShaderType::SOLID),
			opaque(false) {}

		Info(int _texTop, int _texSide, int _texBottom,
			Shape _shape, ShaderType _shaderType, bool _opaque)
		   : texTop(_texTop),
			 texSide(_texSide),
			 texBottom(_texBottom),
			 shape(_shape),
			 shaderType(_shaderType),
			 opaque(_opaque) {}
	};

	struct Data {
		std::unique_ptr<UpdateHandler> updateHandler;
		Info info;

		Data() 
			: updateHandler(std::make_unique<NonUpdatable>())
		{}

		Data(std::unique_ptr<UpdateHandler>&& updater, const Info& _info) 
			: updateHandler(std::move(updater)),
			info(_info)
		{}
	};
}