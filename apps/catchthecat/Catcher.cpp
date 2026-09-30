#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world) {
  std::vector<Point2D> path = generatePath(world);

  if (path.size() == 0)
  {
    if (world->catcherCanMoveToPosition(world->E(world->getCat()))) { return world->E(world->getCat()); }
    if (world->catcherCanMoveToPosition(world->NE(world->getCat()))) { return world->NE(world->getCat()); }
    if (world->catcherCanMoveToPosition(world->NW(world->getCat()))) { return world->NW(world->getCat()); }
    if (world->catcherCanMoveToPosition(world->W(world->getCat()))) { return world->W(world->getCat()); }
    if (world->catcherCanMoveToPosition(world->SW(world->getCat()))) { return world->SW(world->getCat()); }
    if (world->catcherCanMoveToPosition(world->SE(world->getCat()))) { return world->SE(world->getCat()); }

    for (int i = world->getWorldSideSize() * -1; i < world->getWorldSideSize() / 2; i++)
    {
      for (int j = world->getWorldSideSize() * -1; j < world->getWorldSideSize() / 2; j++)
      {
        if (world->catcherCanMoveToPosition(Point2D(i, j))) { return Point2D(i, j); }
      }
    }
  }

  if (world->catcherCanMoveToPosition(path.front()))
  {
    return path.front();
  }

  for (int i = path.size() - 2; i >= 0; i--)
  {
    if (world->catcherCanMoveToPosition(path[i]))
    {
      return path.front();
    }
  }
}