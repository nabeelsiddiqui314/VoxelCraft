#pragma once
#include "Mesh.h"
#include "RenderData.h"

class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();
public:
	void addMesh(const Mesh& mesh);
	void bindVao();
	const RenderData& getRenderData() const;
private:
	RenderData m_renderData;
	GLuint m_vbo;
	GLuint m_ebo;
};

