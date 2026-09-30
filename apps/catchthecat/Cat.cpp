#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world) {
	std::vector<Point2D> path = generatePath(world);

	if (path.size() == 0)
	{
		if (world->catCanMoveToPosition(world->E(world->getCat()))) { return world->E(world->getCat()); }
		if (world->catCanMoveToPosition(world->NE(world->getCat()))) { return world->NE(world->getCat()); }
		if (world->catCanMoveToPosition(world->NW(world->getCat()))) { return world->NW(world->getCat()); }
		if (world->catCanMoveToPosition(world->W(world->getCat()))) { return world->W(world->getCat()); }
		if (world->catCanMoveToPosition(world->SW(world->getCat()))) { return world->SW(world->getCat()); }
		if (world->catCanMoveToPosition(world->SE(world->getCat()))) { return world->SE(world->getCat()); }
	}

	return path.back();
}
