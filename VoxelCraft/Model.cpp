#include "stdafx.h"
#include "Model.h"
#include <GL/glew.h>


Model::Model(const Mesh& mesh) {
	addMesh(mesh);
}

void Model::addMesh(const Mesh& mesh) {
	generateVAO();
	bindVao();

	addVBO(3, mesh.vertices);
	addVBO(2, mesh.textureCoords);
	addIBO(mesh.indices);
}

void Model::generateVAO() {
	if (m_renderData.VAO != 0) {
		this->cleanUp();
	}
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iBuffer.size() * sizeof(GLfloat), &iBuffer.front(), GL_STATIC_DRAW);
}

void Model::bindVao() const {
	glBindVertexArray(m_renderData.VAO);
}

void Model::cleanUp() {
	if (m_renderData.VAO)
		glDeleteVertexArrays(1, &m_renderData.VAO);
	if (m_vBuffer.size() > 0)
		glDeleteBuffers(static_cast<GLsizei>(m_vBuffer.size()), &m_vBuffer.front());
	m_vBuffer.clear();
	m_vBuffer.shrink_to_fit();
	m_vboCount = 0;
	m_ibo = 0;
}

const RenderData& Model::getRenderData() const {
	return m_renderData;
}

Model::~Model() {
	cleanUp();
}
