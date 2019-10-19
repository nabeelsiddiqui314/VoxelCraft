#include "stdafx.h"
#include "NonUpdatable.h"

#include "World.h"

bool NonUpdatable::isUpdatable() const {
	return false;
}

bool NonUpdatable::callUpdate(World& world, int x, int y, int z) {
	return true;
}

int NonUpdatable::getCoolDownTime() const {
	return 0;
}
