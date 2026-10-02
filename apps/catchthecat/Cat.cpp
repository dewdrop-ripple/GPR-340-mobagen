#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world)
{
  if (!allBordersBlocked)
  {
    std::vector<Point2D> path = generatePath(world);

    if (!allBordersBlocked)
    {
      return path.back();
    }
  }

  if (isGoodPosition(world, world->E(world->getCat()))) { return world->E(world->getCat()); }
  if (isGoodPosition(world, world->NE(world->getCat()))) { return world->NE(world->getCat()); }
  if (isGoodPosition(world, world->NW(world->getCat()))) { return world->NW(world->getCat()); }
  if (isGoodPosition(world, world->W(world->getCat()))) { return world->W(world->getCat()); }
  if (isGoodPosition(world, world->SW(world->getCat()))) { return world->SW(world->getCat()); }
  if (isGoodPosition(world, world->SE(world->getCat()))) { return world->SE(world->getCat()); }
}

bool Cat::isGoodPosition(CatWorld* w, Point2D p)
{
  bool open = w->catCanMoveToPosition(p);

  /*
  bool oldPos = false;
  if (!(lastPoint.x * 2 == 1))
  {
    if (p == lastPoint)
    {
      oldPos = true;
    }
  }
  lastPoint = p;
  */

  return open;
}
