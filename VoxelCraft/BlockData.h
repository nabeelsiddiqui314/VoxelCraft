#pragma once
#include <glm/glm.hpp>
#include "BlockCategory.h"

struct BlockData {
	int texCoordTop;
	int texCoordSide;
	int texCoordBottom;

	BlockCategory category;
	bool opaque;

	BlockData() 
	: texCoordTop(0),
	  texCoordSide(0),
	  texCoordBottom(0),
	  category(BlockCategory::SOLID),
	  opaque(false) {}

	BlockData(int _texCoordTop, int _texCoordSide, int _texCoordBottom, const BlockCategory& _category, bool _opaque)
	:   texCoordTop(_texCoordTop),
		texCoordSide(_texCoordSide),
		texCoordBottom(_texCoordBottom),
	  category(_category),
	  opaque(_opaque) {}
};