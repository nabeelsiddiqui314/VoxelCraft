#pragma once
#include <queue>
#include "vector3.h"

class Segment;

class LightingComputer
{
private:
	struct LightVoxel {
		Vector3 pos;
		Segment* parent;

		LightVoxel(Vector3 _pos, Segment* _parent)
			: pos(_pos), parent(_parent) {}
	};
public:
	LightingComputer() = default;
	~LightingComputer() = default;
public:
	void addLight(int x, int y, int z, Segment* segment);
	void propogate();
private:
	int adjustOrdinate(int ordinate);
private:
	std::queue<LightVoxel> m_lightQueue;
};

