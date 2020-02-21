#pragma once
#include "State.h"
#include "../World/World.h"
#include "../OGL/Util/Camera.h"

class Game : public State
{
public:
	Game();
public:
	void update(float dt) override;
	void render(MasterRenderer& renderer) override;
private:
	void editVoxels();
private:
	Camera m_camera;
	World m_world;
};

