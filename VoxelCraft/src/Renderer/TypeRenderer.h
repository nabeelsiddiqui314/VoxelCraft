#pragma once
#include "../OGL/Util/Camera.h"
#include "../OGL/Core/Model.h"
#include "../OGL/Core/Shader.h"
#include "../OGL/Util/TextureAtlas.h"
#include <SFML/System/Clock.hpp>

class TypeRenderer
{
public:
	TypeRenderer(const std::string& vert, const std::string& frag);
public:
	void addModel(const Model* model);
	virtual void render(const Camera& camera, float worldTime) = 0;
protected:
	void updateShader(const Camera& camera, float worldTime);
	void drawModels();
protected:
	Shader p_shader;
private:
	std::vector<const Model*> m_models;
};

