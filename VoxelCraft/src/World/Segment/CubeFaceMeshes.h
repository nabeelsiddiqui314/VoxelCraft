#pragma once
#include <array>
#include <GL/glew.h>

// indices in 0, 1, 2, 0, 2, 3

struct CubeFace {
	const std::array<GLfloat, 12> mesh;
	float light;
};

namespace MeshFace {

	CubeFace front = { {
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0
	}, 0.7f };

	CubeFace back = { {
		1, 0, -1,
		0, 0, -1,
		0, 1, -1,
		1, 1, -1
	}, 0.7f };

	CubeFace left = { {
		0, 0, -1,
		0, 0,  0,
		0, 1,  0,
		0, 1, -1
	}, 0.5f };

	CubeFace right = { {
		1, 0,  0,
		1, 0, -1,
		1, 1, -1,
		1, 1,  0
	}, 0.5f };

	CubeFace top = { {
		0, 1,  0,
		1, 1,  0,
		1, 1, -1,
		0, 1, -1
	}, 1.0f };

	CubeFace bottom = { {
		0, 0, -1,
		1, 0, -1,
		1, 0,  0,
		0, 0,  0
	}, 0.2f };

	CubeFace crossA = { {
		0, 0, -1,
		1, 0,  0,
		1, 1,  0,
		0, 1, -1
	}, 0.5f };

	CubeFace crossB = { {
		1, 0, -1,
		0, 0,  0,
		0, 1,  0,
		1, 1, -1
	}, 0.5f };

}