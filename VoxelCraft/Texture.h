#pragma once
#include <GL/glew.h>
#include "stbi.h"
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& path);
	~Texture();
public:
	void load(const std::string& path);
	void bind(std::uint8_t slot = 0);
	void unbind();
private:
	GLuint m_texture;
	unsigned char* m_buffer;
	int m_width, m_height, m_channels;
};

