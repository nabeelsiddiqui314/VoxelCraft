#pragma once
#include "VoxelCodex.h"
#include "VoxelEnums.h"

namespace Voxel {
	class Element
	{
	public:
		Element();
		Element(Type id);
		~Element() = default;
	public:
		void operator=(const Type& rval);
		bool operator==(const Type& rval) const;
		bool operator!=(const Type& rval) const;

		const Info& getInfo() const;
		const std::unique_ptr<UpdateHandler>& getUpdateHandler() const;
	public:
		Type id;
	};
}