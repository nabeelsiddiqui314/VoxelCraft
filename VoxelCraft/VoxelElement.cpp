#include "stdafx.h"
#include "VoxelElement.h"

namespace Voxel {
	Element::Element() : m_type(Type::VOID), m_naturalLight(2) {}

	Element::Element(Type type) : m_type(type), m_naturalLight(2) {}

	void Element::operator=(const Type& rval) {
		m_type = rval;
	}

	bool Element::operator==(const Type& rval) const {
		return m_type == rval;
	}

	bool Element::operator!=(const Type& rval) const {
		return m_type != rval;
	}

	void Element::setNaturalLight(std::uint8_t luminocity) {
		m_naturalLight = luminocity;
	}

	const Type Element::getType() const {
		return m_type;
	}

	std::uint8_t Element::getNaturalLight() const {
		return m_naturalLight;
	}

	const Info& Element::getInfo() const {
		return Codex::getInstance().getVoxelData(m_type).info;
	}

	const std::unique_ptr<UpdateHandler>& Element::getUpdateHandler() const {
		return Codex::getInstance().getVoxelData(m_type).updateHandler;
	}
}