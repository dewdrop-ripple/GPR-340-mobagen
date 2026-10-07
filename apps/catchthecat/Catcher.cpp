#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world)
{
    if (abs(world->getCat().x) < 1 && abs(world->getCat().y < 1)) { Reset(); }

    Point2D move = Point2D(0.5, 0.5);

    // If there are still border walls
    if (!allBordersBlocked)
    {
        std::vector<Point2D> path = generatePath(world);

        // Set to no border walls
        // Mark off the box the cat is trapped in right now
        if (path.size() == 0)
        {
            allBordersBlocked = true;

            catBoxMinX = (world->getWorldSideSize() / -2) + 1;
            catBoxMaxX = (world->getWorldSideSize() / 2) - 1;
            catBoxMinY = (world->getWorldSideSize() / -2) + 1;
            catBoxMaxY = (world->getWorldSideSize() / 2) - 1;
        }

        // If an open border wall was found
        else
        {
            // If the cat is about to escape, stop it
            if (path.size() <= 2)
            {
                move = path.front();
            }
            // Otherwise leave the gap and block off other walls in the meantime
            else
            {
                move = GetNextLogicalWall(world, path.front());
            }
        }
    }

    if (allBordersBlocked)
    {
        // If the cat is trapped in a 3x3 box or smaller, just start closing off walls next to it
        if ((catBoxMaxX - catBoxMinX) * (catBoxMaxY - catBoxMinY) <= 9)
        {
            if (world->catcherCanMoveToPosition(world->E(world->getCat())) && !world->getContent(world->E(world->getCat()))) { move = world->E(world->getCat()); }
            else if (world->catcherCanMoveToPosition(world->NE(world->getCat())) && !world->getContent(world->NE(world->getCat()))) { move = world->NE(world->getCat()); }
            else if (world->catcherCanMoveToPosition(world->NW(world->getCat())) && !world->getContent(world->NW(world->getCat()))) { move = world->NW(world->getCat()); }
            else if (world->catcherCanMoveToPosition(world->W(world->getCat())) && !world->getContent(world->W(world->getCat()))) { move = world->W(world->getCat()); }
            else if (world->catcherCanMoveToPosition(world->SW(world->getCat())) && !world->getContent(world->SW(world->getCat()))) { move = world->SW(world->getCat()); }
            else if (world->catcherCanMoveToPosition(world->SE(world->getCat())) && !world->getContent(world->SE(world->getCat()))) { move = world->SE(world->getCat()); }
        }

        // Cut the longer side in half
        else if (catBoxMaxX - catBoxMinX > catBoxMaxY - catBoxMinY)
        {
            int xValue = (catBoxMaxX + catBoxMinX) / 2;
            for (int i = catBoxMinY; i <= catBoxMaxY; i++)
            {
                Point2D point = Point2D(xValue, i);
                if (world->catcherCanMoveToPosition(point) && !world->getContent(point))
                {
                    move = point;
                }
            }

            // Adjust bounds as needed
            if (world->getCat().x > xValue)
            {
                catBoxMinX = xValue + 1;
            }
            else
            {
                catBoxMaxX = xValue - 1;
            }
        }
        else
        {
            int yValue = (catBoxMaxY + catBoxMinY) / 2;
            for (int i = catBoxMinX; i <= catBoxMaxX; i++)
            {
                Point2D point = Point2D(i, yValue);
                if (world->catcherCanMoveToPosition(point) && !world->getContent(point))
                {
                    move = point;
                }
            }

            // Adjust bounds as needed
            if (world->getCat().y > yValue)
            {
                catBoxMinY = yValue + 1;
            }
            else
            {
                catBoxMaxY = yValue - 1;
            }
        }
    }

    world->lastMove = move;
    return move;
}

// Given a wall, iterate around the edge of the map clockwise and counterclockwise to find another wall to block
Point2D Catcher::GetNextLogicalWall(CatWorld* world, Point2D wall)
{
    int leftWall =(world->getWorldSideSize() / -2);
    int rightWall =(world->getWorldSideSize() / 2);
    int bottomWall = (world->getWorldSideSize() / -2);
    int topWall = (world->getWorldSideSize() / 2);

    Point2D targetPointCW = wall;
    Point2D targetPointCCW = wall;

    while (true)
    {
        if (targetPointCW.x == leftWall && targetPointCW.y != topWall) { targetPointCW.y++; }
        else if (targetPointCW.y == topWall && targetPointCW.x != rightWall) { targetPointCW.x++; }
        else if (targetPointCW.x == rightWall && targetPointCW.y != bottomWall) { targetPointCW.y--; }
        else if (targetPointCW.y == bottomWall && targetPointCW.x != leftWall) { targetPointCW.x--; }

        if (world->catcherCanMoveToPosition(targetPointCW) && !world->getContent(targetPointCW)) { return targetPointCW; }

        if (targetPointCCW.x == leftWall && targetPointCCW.y != bottomWall) { targetPointCCW.y--; }
        else if (targetPointCCW.y == bottomWall && targetPointCCW.x != rightWall) { targetPointCCW.x++; }
        else if (targetPointCCW.x == rightWall && targetPointCCW.y != topWall) { targetPointCCW.y++; }
        else if (targetPointCCW.y == topWall && targetPointCCW.x != leftWall) { targetPointCCW.x--; }

        if (world->catcherCanMoveToPosition(targetPointCCW) && !world->getContent(targetPointCCW)) { return targetPointCCW; }
    }
}

void Catcher::Reset()
{
    catBoxMinX = NULL;
    catBoxMaxX = NULL;
    catBoxMinY = NULL;
    catBoxMaxY = NULL;

    allBordersBlocked = false;
}