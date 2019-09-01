#include "stdafx.h"
#include "MeshGenerator.h"

void MeshGenerator::addFace(std::int16_t x, std::int16_t y, std::int16_t z, const std::array<GLfloat, 12>& face) {
	m_mesh.textureCoords.insert(m_mesh.textureCoords.end(),  {
			0, 0,
			1, 0,
			1, 1,
			0, 1
		} );

	m_mesh.indices.insert(m_mesh.indices.end(), {
			m_index,
			m_index + 1,
			m_index + 2,
			m_index,
			m_index + 2,
			m_index + 3
		});
	m_index += 4;

	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_mesh.vertices.push_back(x + face[faceIndex++]);
		m_mesh.vertices.push_back(y + face[faceIndex++]);
		m_mesh.vertices.push_back(z + face[faceIndex++]);
	}
}

void MeshGenerator::cleanUp() {
	m_mesh.vertices.clear();
	m_mesh.textureCoords.clear();
	m_mesh.indices.clear();

	m_mesh.vertices.shrink_to_fit();
	m_mesh.textureCoords.shrink_to_fit();
	m_mesh.indices.shrink_to_fit();
}

const Mesh& MeshGenerator::getMesh() const {
	return m_mesh;
}