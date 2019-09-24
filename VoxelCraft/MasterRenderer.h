#pragma once
#include "SolidRenderer.h"
#include "ChunkModelsMaker.h"
#include <GLFW/glfw3.h>

class MasterRenderer
{
public:
	MasterRenderer();
public:
	void addChunk(const Model& models);
	void render(GLFWwindow* window, const Camera& camera);
private:
	SolidRenderer m_solidRenderer;
	
};

