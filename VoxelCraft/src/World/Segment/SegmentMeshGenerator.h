#pragma once
#include <array>

struct Vector3;
class Segment;
struct MeshTypes;
class SegmentMesh;

namespace Voxel {
	class Element;
}

class SegmentMeshGenerator {
private:
	typedef std::array<Voxel::Element, 7> Neighbors;
public:
	static void generateMesh(MeshTypes& meshes, const Vector3& worldPos, const Segment& segment);
private:
	static void addCubeFace(SegmentMesh* mesh, const Neighbors& neighbors, int x, int y, int z, int neighbor);
};