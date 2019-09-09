#include "stdafx.h"
#include "TextureAtlas.h"

Texture TextureAtlas::s_texture;
int TextureAtlas::s_width = 1;

void TextureAtlas::init(int width) {
	s_texture.load("res/textureAtlas.png");
	s_texture.bind();
	s_width = width;
}

const sf::Vector2f TextureAtlas::getTexCoords(int index) {
	return sf::Vector2f((float)(index % s_width) / (float)s_width, (float)floor(index / s_width) / (float)s_width);
}

float TextureAtlas::getUnitLength() {
	return 1.0f / (float)s_width;
}
