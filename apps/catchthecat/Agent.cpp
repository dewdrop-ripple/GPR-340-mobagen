#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"

using namespace std;

bool Agent::isVisitable(CatWorld* w, const std::unordered_map<Point2D, bool>& visited, const Point2D& point)
{
  // Not visited, not cat, and not wall
  bool alreadyVisited;

  try
  {
    alreadyVisited = visited.at(point);
  }
  catch (const exception& e)
  {
    alreadyVisited = false;
  }

  bool canVisit = !alreadyVisited && (w->getCat() != point) && !w->getContent(point);
  return canVisit;
}

std::vector<Point2D> Agent::getVisitableNeightbors(CatWorld* w, const std::unordered_map<Point2D, bool>& visited, const Point2D& current)
{
  std::vector<Point2D> neighbours = vector<Point2D>();

  if (isVisitable(w, visited, w->NE(current))) { neighbours.push_back(w->NE(current)); }
  if (isVisitable(w, visited, w->NW(current))) { neighbours.push_back(w->NW(current)); }
  if (isVisitable(w, visited, w->SE(current))) { neighbours.push_back(w->SE(current)); }
  if (isVisitable(w, visited, w->SW(current))) { neighbours.push_back(w->SW(current)); }
  if (isVisitable(w, visited, w->E(current))) { neighbours.push_back(w->E(current)); }
  if (isVisitable(w, visited, w->W(current))) { neighbours.push_back(w->W(current)); }

  return neighbours;
}

std::vector<Point2D> Agent::generatePath(CatWorld* w)
{
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<PriorityQueuePoint2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(PriorityQueuePoint2D(catPos, 0));
  frontierSet.insert(catPos);
  Point2D borderExit = {INT32_MAX, INT32_MAX};  // sentinel: no border found yet
  bool borderFound = false;

  while (!(frontier.empty() || borderFound))
  {
    // get the current from frontier
    PriorityQueuePoint2D current = frontier.top();

    // remove the current from frontierset
    frontier.pop();

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> nieghbors = getVisitableNeightbors(w, visited, current.mPoint);

    // iterate over the neighs:
    for (auto n : nieghbors)
    {
      // for every neighbor set the cameFrom
      cameFrom.insert({n, current.mPoint});

      // enqueue the neighbors to frontier and frontierset
      frontier.push(PriorityQueuePoint2D(n, current.mPriority + min((w->getWorldSideSize()/2 - abs(n.x)), (w->getWorldSideSize()/2 - abs(n.y)))));
      frontierSet.insert(n);

      // mark current as visited
      visited.insert(pair<Point2D, bool>(n, true));

      // do this up to find a visitable border and break the loop
      if (w->catWinsOnSpace(n))
      {
        borderExit = n;
        borderFound = true;
        break;
      }
    }
  }

  if (borderFound)
  {
    // if the border is not infinity, build the path from border to the cat using the camefrom map
    vector<Point2D> path = vector<Point2D>();
    Point2D targetPoint = borderExit;
    bool pathComplete = false;

    while (!pathComplete)
    {
      if (targetPoint == catPos)
      {
        pathComplete = true;
      }
      else
      {
        path.push_back(targetPoint);
        targetPoint = cameFrom.at(targetPoint);
      }
    }

    // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
    return path;
  }

  // if there isnt a reachable border, just return empty vector
  return vector<Point2D>();
}
