#include "stdafx.h"
#include "Model.h"
#include <GL/glew.h>


Model::Model()
	: m_vboCount(0),
	  m_ibo(0) {}

void Model::addMesh(const Mesh& mesh) {
	cleanUp();

	generateVAO();
	bindVao();

	addVBO(3, mesh.vertices);
	addVBO(2, mesh.textureCoords);
	addVBO(1, mesh.naturalLight);
	addVBO(1, mesh.skyExposure);
	addIBO(mesh.indices);
}

void Model::generateVAO() {
	glGenVertexArrays(1, &m_renderData.VAO);
}

void Model::addVBO(GLuint size, const std::vector<GLfloat>& buffer) {
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer.size() * sizeof(GLfloat), &buffer.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(static_cast<GLuint>(m_vboCount));
	glVertexAttribPointer(static_cast<GLuint>(m_vboCount), size, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_vboCount++;
	m_vBuffer.push_back(vbo);
}

void Model::addIBO(const std::vector<GLuint>& iBuffer) {
	m_renderData.indicesCount = iBuffer.size();
	glGenBuffers(1, &m_ibo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iBuffer.size() * sizeof(GLuint), &iBuffer.front(), GL_STATIC_DRAW);
}

void Model::bindVao() const {
	glBindVertexArray(m_renderData.VAO);
}

const RenderData& Model::getRenderData() const {
	return m_renderData;
}

void Model::deleteBuffers() {
	for (auto& vBuffer : m_vBuffer) {
		glDeleteBuffers(1, &vBuffer);
	}
	glDeleteBuffers(1, &m_ibo);
    glDeleteVertexArrays(1, &m_renderData.VAO);

	cleanUp();
}

bool Model::hasData() {
	return m_renderData.VAO != 0;
}

void Model::cleanUp() {
	m_renderData.VAO = 0;
	m_renderData.indicesCount = 0;
	m_vboCount = 0;
	m_ibo = 0;
	m_vBuffer.clear();
}