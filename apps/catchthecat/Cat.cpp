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
    bool moveFound = false;
    while (!moveFound)
    {
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();
    switch (rand)
    {
      case 0:
        if (world->catCanMoveToPosition(world->NE(pos)))
        {
          moveFound = true;
          move = world->NE(pos);
        }
        break;
      case 1:
        if (world->catCanMoveToPosition(world->NW(pos)))
        {
          moveFound = true;
          move = world->NW(pos);
        }
        break;
      case 2:
        if (world->catCanMoveToPosition(world->E(pos)))
        {
          moveFound = true;
          move = world->E(pos);
        }
        break;
      case 3:
        if (world->catCanMoveToPosition(world->W(pos)))
        {
          moveFound = true;
          move = world->W(pos);
        }
        break;
      case 4:
        if (world->catCanMoveToPosition(world->SW(pos)))
        {
          moveFound = true;
          move = world->SW(pos);
        }
        break;
      case 5:
        if (world->catCanMoveToPosition(world->SE(pos)))
        {
          moveFound = true;
          move = world->SE(pos);
        }
        break;
      default:
        throw std::runtime_error("random out of range");
    }
    }
  }

  world->lastMove = move;
  return move;
}

void Cat::Reset()
{
  allBordersBlocked = false;
}