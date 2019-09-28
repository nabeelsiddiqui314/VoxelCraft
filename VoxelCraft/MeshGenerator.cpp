#include "stdafx.h"
#include "MeshGenerator.h"

MeshGenerator::MeshGenerator(Mesh& mesh) : m_mesh(mesh) {}

void MeshGenerator::addFace(std::int16_t x, std::int16_t y, std::int16_t z, int textureIndex, const std::array<GLfloat, 12>& face, GLfloat lightFactor) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_mesh.vertices.emplace_back(x + face[faceIndex++]);
		m_mesh.vertices.emplace_back(y + face[faceIndex++]);
		m_mesh.vertices.emplace_back(z + face[faceIndex++]);
		m_mesh.lightFactorData.emplace_back(lightFactor);
	}

	sf::Vector2f texCoord = TextureAtlas::getTexCoords(textureIndex);
	m_mesh.textureCoords.insert(m_mesh.textureCoords.end(),  {
			texCoord.x                                , texCoord.y,
			texCoord.x + TextureAtlas::getUnitLength(), texCoord.y,
			texCoord.x + TextureAtlas::getUnitLength(), texCoord.y + TextureAtlas::getUnitLength(),
			texCoord.x                                , texCoord.y + TextureAtlas::getUnitLength()
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
}