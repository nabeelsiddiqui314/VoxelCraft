#include "stdafx.h"
#include "Model.h"
#include <GL/glew.h>


Model::Model(const Mesh& mesh) {
	addMesh(mesh);
}


Model::~Model() {

}

void Model::addMesh(const Mesh& mesh) {
	m_renderData.indicesCount = mesh.indices.size();

	glGenVertexArrays(1, &m_renderData.VAO);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	glBindVertexArray(m_renderData.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, (mesh.vertices.size()) * sizeof(GLfloat), &mesh.vertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLfloat), &mesh.indices.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

	glBindVertexArray(0);
}

void Model::bindVao() {
	glBindVertexArray(m_renderData.VAO);
}

const RenderData& Model::getRenderData() const {
	return m_renderData;
}
