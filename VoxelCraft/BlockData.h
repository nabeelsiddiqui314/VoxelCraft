#pragma once
#include <glm/glm.hpp>
#include "ShaderType.h"
#include "BlockShape.h"
#include "BlockUpdateHandler.h"
#include <memory>

struct BlockData {
	std::unique_ptr<BlockUpdateHandler> updateHandler;

	int texTop;
	int texSide;
	int texBottom;

	BlockShape shape;
	ShaderType shaderType;
	bool opaque;

	BlockData() 
	: updateHandler(std::make_unique<BlockUpdateHandler>()),
	  texTop(0),
	  texSide(0),
	  texBottom(0),
	  shape(BlockShape::CUBE),
	  shaderType(ShaderType::SOLID),
	  opaque(false) {}

	BlockData(std::unique_ptr<BlockUpdateHandler> blockUpdater, int _texTop, int _texSide, int _texBottom,
		BlockShape _shape, ShaderType _shaderType, bool _opaque)
	:   updateHandler(std::move(blockUpdater)),
		texTop   (_texTop),
		texSide  (_texSide),
		texBottom(_texBottom),
		shape(_shape),
		shaderType(_shaderType),
	     opaque(_opaque) {}
};