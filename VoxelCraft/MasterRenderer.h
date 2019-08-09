#pragma once
#include "Camera.h"
#include "OpaqueRenderer.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include <GLFW/glfw3.h>

class MasterRenderer
{
public:
	MasterRenderer();
public:
	void addChunk(const Model& model);
	void render(GLFWwindow* window, const Camera& camera);
private:
	std::vector<Model> m_chunks;
	OpaqueRenderer m_blockRenderer;
	//temp
	Shader m_shader;
	Texture m_tex;
};

