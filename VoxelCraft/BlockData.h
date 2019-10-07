#pragma once
#include <glm/glm.hpp>
#include "ShaderType.h"
#include "BlockShape.h"

struct BlockData {
	int texTop;
	int texSide;
	int texBottom;

	BlockShape shape;
	ShaderType shaderType;
	bool opaque;

	BlockData() 
	: texTop(0),
	  texSide(0),
	  texBottom(0),
	  shape(BlockShape::CUBE),
	  shaderType(ShaderType::SOLID),
	  opaque(false) {}

	BlockData(int _texTop, int _texSide, int _texBottom, BlockShape _shape, ShaderType _shaderType, bool _opaque)
	:   texTop   (_texTop),
		texSide  (_texSide),
		texBottom(_texBottom),
		shape(_shape),
		shaderType(_shaderType),
	     opaque(_opaque) {}
};