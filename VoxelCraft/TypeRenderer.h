#pragma once
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "TextureAtlas.h"

class TypeRenderer
{
public:
	TypeRenderer(const std::string& shader);
public:
	void addModel(const Model* model);
	virtual void render(const Camera& camera) = 0;
protected:
	void handleCameraTransform(const Camera& camera);
	void drawModels();
private:
	std::vector<const Model*> m_models;
	Shader m_shader;
};

