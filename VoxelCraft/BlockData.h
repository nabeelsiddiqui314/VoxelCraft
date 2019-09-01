#pragma once
#include <glm/glm.hpp>
#include "BlockCategory.h"

struct BlockData {
	glm::vec2 topTexCoord;
	glm::vec2 sideTexCoord;
	glm::vec2 bottomTexCoord;

	BlockCategory category;
	bool opaque;

	BlockData() 
	: topTexCoord(0, 0),
	  sideTexCoord(0, 0), 
	  bottomTexCoord(0, 0),
	  category(BlockCategory::SOLID),
	  opaque(false) {}

	BlockData(const glm::vec2& _topTexCoord, const glm::vec2& _sideTexCoord, 
		const glm::vec2& _bottomTexCoord, const BlockCategory& _category, bool _opaque) 
	: topTexCoord(_topTexCoord),
	  sideTexCoord(_sideTexCoord),
	  bottomTexCoord(_bottomTexCoord),
	  category(_category),
	  opaque(_opaque) {}
};