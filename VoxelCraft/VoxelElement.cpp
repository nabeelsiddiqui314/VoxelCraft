#include "stdafx.h"
#include "VoxelElement.h"

namespace Voxel {
	Element::Element() : id(Type::VOID) {}

	Element::Element(Type id) : id(id) {}

	void Element::operator=(const Type& rval) {
		id = rval;
	}

	bool Element::operator==(const Type& rval) const {
		return id == rval;
	}

	bool Element::operator!=(const Type& rval) const {
		return id != rval;
	}

	const Info& Element::getInfo() const {
		return Codex::getVoxelData(id).info;
	}

	const std::unique_ptr<UpdateHandler>& Element::getUpdateHandler() const {
		return Codex::getVoxelData(id).updateHandler;
	}
}