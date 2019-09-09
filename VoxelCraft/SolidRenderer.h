#pragma once
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class SolidRenderer
{
public:
	SolidRenderer();
	~SolidRenderer();
public:
	void addSolidChunk(const Model* solid);
	void render(const Camera& camera);
private:
	std::vector<const Model*> m_solidChunks;
	Shader m_shader;
	Texture m_texture;
};

