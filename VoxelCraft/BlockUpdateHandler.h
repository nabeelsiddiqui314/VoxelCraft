#pragma once
#include "NonCopyable.h"
#include <SFML/System/Clock.hpp>

class World;

class BlockUpdateHandler : public NonCopyable
{
public:
	BlockUpdateHandler() = default;
	virtual ~BlockUpdateHandler() {}
public:
	bool update(World& world, int x, int y, int z);
	virtual bool isUpdatable() const;
protected:
	virtual bool callUpdate(World& world, int x, int y, int z) = 0;
	virtual int getCoolDownTime() const = 0;
private:
	sf::Clock m_coolDownTimer;
};