#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world)
{
  // Don't rebuild the path if you know there is none
  if (!allBordersBlocked)
  {
    // Builds path and checks if there is none
    std::vector<Point2D> path = generatePath(world);

    // If there is a path, move down it
    if (!allBordersBlocked)
    {
      return path.back();
    }
  }

  // If no path, move to a random position that isn't where the cat just was
  if (isGoodPosition(world, world->E(world->getCat()))) { lastPoint = world->E(world->getCat()); return world->E(world->getCat()); }
  if (isGoodPosition(world, world->NE(world->getCat()))) { lastPoint = world->NE(world->getCat()); return world->NE(world->getCat()); }
  if (isGoodPosition(world, world->NW(world->getCat()))) { lastPoint = world->NW(world->getCat()); return world->NW(world->getCat()); }
  if (isGoodPosition(world, world->W(world->getCat()))) { lastPoint = world->W(world->getCat()); return world->W(world->getCat()); }
  if (isGoodPosition(world, world->SW(world->getCat()))) { lastPoint = world->SW(world->getCat()); return world->SW(world->getCat()); }
  if (isGoodPosition(world, world->SE(world->getCat()))) { lastPoint = world->SE(world->getCat()); return world->SE(world->getCat()); }

  // If trapped in a 1x2 spot, just move where you can
  if (world->catCanMoveToPosition(world->E(world->getCat()))) { lastPoint = world->E(world->getCat()); return world->E(world->getCat()); }
  if (world->catCanMoveToPosition(world->NE(world->getCat()))) { lastPoint = world->NE(world->getCat()); return world->NE(world->getCat()); }
  if (world->catCanMoveToPosition(world->NW(world->getCat()))) { lastPoint = world->NW(world->getCat()); return world->NW(world->getCat()); }
  if (world->catCanMoveToPosition(world->W(world->getCat()))) { lastPoint = world->W(world->getCat()); return world->W(world->getCat()); }
  if (world->catCanMoveToPosition(world->SW(world->getCat()))) { lastPoint = world->SW(world->getCat()); return world->SW(world->getCat()); }
  if (world->catCanMoveToPosition(world->SE(world->getCat()))) { lastPoint = world->SE(world->getCat()); return world->SE(world->getCat()); }
}

// Checks if a spot is not a wall and is not where the cat just was
bool Cat::isGoodPosition(CatWorld* w, Point2D p)
{
  bool open = w->catCanMoveToPosition(p);

  bool oldPos = false;
  if (!(lastPoint.x * 2 == 1))
  {
    if (p.x == lastPoint.x && p.y == lastPoint.y)
    {
      oldPos = true;
    }
  };

  return open && !oldPos;
}