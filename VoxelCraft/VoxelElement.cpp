#include "stdafx.h"
#include "VoxelElement.h"

namespace Voxel {
	Element::Element() : m_type(Type::VOID) {}

	Element::Element(Type type) : m_type(type) {}

	void Element::operator=(const Type& rval) {
		m_type = rval;
	}

	bool Element::operator==(const Type& rval) const {
		return m_type == rval;
	}

	bool Element::operator!=(const Type& rval) const {
		return m_type != rval;
	}

	const Type Element::getType() const {
		return m_type;
	}

	const Info& Element::getInfo() const {
		return Codex::getInstance().getVoxelData(m_type).info;
	}

	const std::unique_ptr<UpdateHandler>& Element::getUpdateHandler() const {
		return Codex::getInstance().getVoxelData(m_type).updateHandler;
	}
}