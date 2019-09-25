#pragma once
#include "SolidRenderer.h"
#include "SegmentModel.h"
#include <GLFW/glfw3.h>

class MasterRenderer
{
public:
	MasterRenderer();
public:
	void addChunk(const MeshTypes& models);
	void render(GLFWwindow* window, const Camera& camera);
private:
	SolidRenderer m_solidRenderer;
	
};

