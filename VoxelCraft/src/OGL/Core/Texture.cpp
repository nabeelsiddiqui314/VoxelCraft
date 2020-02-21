#include "Texture.h"

Texture::Texture()
:  m_texture(0),
   m_buffer(nullptr),
   m_width(0),
   m_height(0), 
   m_channels(0)
{}

Texture::Texture(const std::string& path)
 : m_texture(0),
   m_buffer(nullptr),
   m_width(0),
   m_height(0), 
   m_channels(0) {
	load(path);
}

void Texture::load(const std::string & path) {
	stbi_set_flip_vertically_on_load(1);
	m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	this->unbind();

	if (m_buffer)
		stbi_image_free(m_buffer);
}

void Texture::bind(std::uint8_t slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture);
}

