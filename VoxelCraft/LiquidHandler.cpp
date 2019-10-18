#include "stdafx.h"
#include "LiquidHandler.h"
#include "World.h"

bool LiquidHandler::callUpdate(World& world, int x, int y, int z) {
	auto liquid = world.getBlock(x, y, z);

	auto tryAdd = [&](int Xoff, int Yoff, int Zoff) {
		if (world.getBlock(Xoff, Yoff, Zoff) == BlockType::VOID) {
			world.setBlock(Xoff, Yoff, Zoff, liquid);
		}
	};

	auto trysideAdd = [&](int Xoff, int Zoff) {
		if (world.getBlock(x, y - 1, z) != BlockType::VOID &&
			world.getBlock(x, y - 1, z) != liquid) {
			tryAdd(Xoff, y, Zoff);
			tryAdd(Xoff, y - 1, Zoff);
		}
	};

	trysideAdd(x + 1, z    );
	trysideAdd(x - 1, z    );
	trysideAdd(x,     z + 1);
	trysideAdd(x,     z - 1);

	tryAdd(x, y - 1, z);

	return true;
}

int LiquidHandler::getCoolDownTime() const {
	return 0;
}
