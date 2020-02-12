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

		void setNaturalLight(std::uint8_t luminocity);

		const Type getType() const;
		std::uint8_t getNaturalLight() const;
		std::uint8_t getSkyExposure() const;

		const Info& getInfo() const;
		const std::unique_ptr<UpdateHandler>& getUpdateHandler() const;
	private:
		Type m_type;
		std::uint8_t m_naturalLight;
	};
}