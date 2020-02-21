#include "SegmentMesh.h"
#include "../../OGL/Core/Mesh.h"
#include "../../OGL/Util/TextureAtlas.h"
#include <SFML/System/Vector2.hpp>

SegmentMesh::SegmentMesh(Mesh& mesh) : m_mesh(mesh) {}

void SegmentMesh::addFace(std::int16_t x, std::int16_t y, std::int16_t z, int textureIndex, const std::array<GLfloat, 12>& face, GLfloat natLight, GLfloat skyExposure) {
	int faceIndex = 0;
	for (int i = 0; i < 4; i++) {
		m_mesh.vertices.emplace_back(x + face[faceIndex++]);
		m_mesh.vertices.emplace_back(y + face[faceIndex++]);
		m_mesh.vertices.emplace_back(z + face[faceIndex++]);
		m_mesh.naturalLight.emplace_back(natLight);
		m_mesh.skyExposure.emplace_back(skyExposure);
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