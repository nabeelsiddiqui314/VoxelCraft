#include "NonUpdatable.h"
#include "../../World.h"

namespace Voxel {
	bool NonUpdatable::isUpdatable() const {
		return false;
	}

	bool NonUpdatable::callUpdate(World& world, int x, int y, int z) {
		return true;
	}

	int NonUpdatable::getCoolDownTime() const {
		return 0;
	}
}