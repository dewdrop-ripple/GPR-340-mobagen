#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(CatWorld* world)
{
  if (abs(world->getCat().x) < 1 && abs(world->getCat().y < 1)) { Reset(); }

  Point2D move = Point2D(0.5, 0.5);

  // Don't rebuild the path if you know there is none
  if (!allBordersBlocked)
  {
    // Builds path and checks if there is none
    std::vector<Point2D> path = generatePath(world);

    // If there is a path, move down it
    if (path.size() == 0)
    {
      allBordersBlocked = true;
    }
    else
    {
      move = path.back();
    }
  }

  if (allBordersBlocked)
  {
    // If no path, move to a random position that isn't where the cat just was
    if (isGoodPosition(world, world->E(world->getCat()))) { lastPoint = world->E(world->getCat()); move = world->E(world->getCat()); }
    else if (isGoodPosition(world, world->NE(world->getCat()))) { lastPoint = world->NE(world->getCat()); move = world->NE(world->getCat()); }
    else if (isGoodPosition(world, world->NW(world->getCat()))) { lastPoint = world->NW(world->getCat()); move = world->NW(world->getCat()); }
    else if (isGoodPosition(world, world->W(world->getCat()))) { lastPoint = world->W(world->getCat()); move = world->W(world->getCat()); }
    else if (isGoodPosition(world, world->SW(world->getCat()))) { lastPoint = world->SW(world->getCat()); move = world->SW(world->getCat()); }
    else if (isGoodPosition(world, world->SE(world->getCat()))) { lastPoint = world->SE(world->getCat()); move = world->SE(world->getCat()); }

    // If trapped in a 1x2 spot, just move where you can
    else if (world->catCanMoveToPosition(world->E(world->getCat()))) { lastPoint = world->E(world->getCat()); move = world->E(world->getCat()); }
    else if (world->catCanMoveToPosition(world->NE(world->getCat()))) { lastPoint = world->NE(world->getCat()); move = world->NE(world->getCat()); }
    else if (world->catCanMoveToPosition(world->NW(world->getCat()))) { lastPoint = world->NW(world->getCat()); move = world->NW(world->getCat()); }
    else if (world->catCanMoveToPosition(world->W(world->getCat()))) { lastPoint = world->W(world->getCat()); move = world->W(world->getCat()); }
    else if (world->catCanMoveToPosition(world->SW(world->getCat()))) { lastPoint = world->SW(world->getCat()); move = world->SW(world->getCat()); }
    else if (world->catCanMoveToPosition(world->SE(world->getCat()))) { lastPoint = world->SE(world->getCat()); move = world->SE(world->getCat()); }
  }

  world->lastMove = move;
  return move;
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

void Cat::Reset()
{
  lastPoint = Point2D(0.5, 0.5);

  allBordersBlocked = false;
}