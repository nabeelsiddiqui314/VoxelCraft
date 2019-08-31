#pragma once
#include "Model.h"
#include <optional>

struct ModelType {
	std::optional<Model> model;
	Mesh mesh;
};