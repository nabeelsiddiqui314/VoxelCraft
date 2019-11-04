#pragma once
#include "Texture.h"
#include <SFML/System/Vector2.hpp>

class TextureAtlas
{
private:
	TextureAtlas() = delete;
public:
	static void init(int width);
	static const sf::Vector2f getTexCoords(int index);
	static float getUnitLength();
private:
	static Texture s_texture;
	static int s_width;
};

