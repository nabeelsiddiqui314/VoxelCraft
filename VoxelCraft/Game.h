#pragma once
#include "State.h"
#include "World.h"

class Game : public State
{
public:
	Game();
public:
	void update(float dt) override;
	void render(MasterRenderer& renderer) override;
private:
	Camera m_camera;
	World m_world;
};

