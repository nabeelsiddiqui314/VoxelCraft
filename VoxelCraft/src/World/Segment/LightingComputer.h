#pragma once
#include <queue>
#include "../../Math/vector3.h"

class Segment;

class LightingComputer
{
private:
	struct LightNode {
		Vector3 pos;
		Segment* parent;

		LightNode(Vector3 _pos, Segment* _parent)
			: pos(_pos), parent(_parent) {}
	};

	struct LightRemovalNode {
		Vector3 pos;
		Segment* parent;
		std::uint8_t lvl;

		LightRemovalNode(Vector3 _pos, Segment* _parent, std::uint8_t _lvl)
			: pos(_pos), parent(_parent), lvl(_lvl) {}
	};
public:
	LightingComputer() = default;
	~LightingComputer() = default;
public:
	void addLight(int x, int y, int z, Segment* segment);
	void removeLight(int x, int y, int z, Segment* segment, int lightlevel);
	void propogate();
private:
	void propogateAdd();
	void propogateRemove();
private:
	std::queue<LightNode> m_lightQueue;
	std::queue<LightRemovalNode> m_lightRemovalQueue;
};

