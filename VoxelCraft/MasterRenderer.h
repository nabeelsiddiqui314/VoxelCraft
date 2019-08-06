#pragma once
#include "Camera.h"
#include "OpaqueRenderer.h"
#include <GLFW/glfw3.h>

class MasterRenderer
{
public:
	MasterRenderer() = default;
public:
	void render(GLFWwindow* window, const Camera& camera);
private:
	OpaqueRenderer m_chunkRenderer;
};

