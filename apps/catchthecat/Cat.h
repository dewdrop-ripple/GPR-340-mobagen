#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat : public Agent
{
  Point2D lastPoint = Point2D(0.5, 0.5);

  bool isGoodPosition(CatWorld* w, Point2D p);

public:
  explicit Cat() : Agent(){};
  Point2D Move(CatWorld*) override;
};

#endif  // CAT_H
