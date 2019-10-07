#pragma once
#include "State.h"
#include "World.h"
#include "Raycast.h"

class Game : public State
{
public:
	Game();
public:
	void update(float dt) override;
	void render(MasterRenderer& renderer) override;
private:
	void editBlocks();
private:
	Camera m_camera;
	World m_world;
};

