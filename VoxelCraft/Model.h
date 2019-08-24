#pragma once
#include "Mesh.h"
#include "RenderData.h"
#include <iostream>

class Model
{
public:
	Model();
	~Model();
public:
	void addMesh(const Mesh& mesh);
	void generateVAO();
	void addVBO(GLuint size, const std::vector<GLfloat>& buffer);
	void addIBO(const std::vector<GLuint>& iBuffer);
	void bindVao() const;
	void cleanUp();
	const RenderData& getRenderData() const;
private:
	RenderData m_renderData;
	std::vector<GLuint> m_vBuffer;
	std::size_t m_vboCount;
	GLuint m_ibo;
};

