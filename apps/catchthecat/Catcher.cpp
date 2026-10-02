#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world)
{
    // If there are still border walls
    if (!allBordersBlocked)
    {
        std::vector<Point2D> path = generatePath(world);

        std::cout << path.size() << std::endl;

        // Set to no border walls
        // Mark off the box the cat is trapped in right now
        if (allBordersBlocked)
        {
            catBoxMinX = (world->getWorldSideSize() / -2) + 1;
            catBoxMaxX = (world->getWorldSideSize() / 2) - 1;
            catBoxMinY = (world->getWorldSideSize() / -2) + 1;
            catBoxMaxY = (world->getWorldSideSize() / 2) - 1;
        }

        // If an open border wall was found
        // Block of logical next border wall
        else
        {
            std::cout << "Open border wall at (" << path.front().x << "," << path.front().y << ")" << std::endl;
            return path.front();
        }
    }

    while (true)
    {
        if (catBoxMaxX - catBoxMinX > catBoxMaxY - catBoxMinY)
        {
            int xValue = (catBoxMaxX + catBoxMinX) / 2;
            for (int i = catBoxMinY; i <= catBoxMaxY; i++)
            {
                Point2D point = Point2D(xValue, i);
                if (world->catcherCanMoveToPosition(point) && !world->getContent(point))
                {
                    std::cout << "Cat in box (" << catBoxMinX << "," << catBoxMaxX << "," << catBoxMinY << "," << catBoxMaxY << ")" << std::endl;
                    return point;
                }
            }

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
                    std::cout << "Cat in box (" << catBoxMinX << "," << catBoxMaxX << "," << catBoxMinY << "," << catBoxMaxY
                        << "), placing block (" << point.x << ", " << point.y << ")" << std::endl;
                    return point;
                }
            }

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
}