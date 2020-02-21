#pragma once
#include "Mesh.h"
#include "RenderData.h"
#include <iostream>

class Model
{
public:
	Model();
public:
	void addMesh(const Mesh& mesh);
	void generateVAO();
	void addVBO(GLuint size, const std::vector<GLfloat>& buffer);
	void addIBO(const std::vector<GLuint>& iBuffer);
	void bindVao() const;
	const RenderData& getRenderData() const;
	void deleteBuffers();
	bool hasData();
private:
	void cleanUp();
private:
	RenderData m_renderData;
	std::vector<GLuint> m_vBuffer;
	std::size_t m_vboCount;
	GLuint m_ibo;
};

