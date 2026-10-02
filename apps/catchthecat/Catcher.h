#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher : public Agent {
  int catBoxMinX = NULL;
  int catBoxMaxX = NULL;
  int catBoxMinY = NULL;
  int catBoxMaxY = NULL;

public:
  explicit Catcher() : Agent(){};
  Point2D Move(CatWorld*) override;
};

#endif  // CATCHER_H
