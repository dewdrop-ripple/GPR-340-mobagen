#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat : public Agent
{
  void Reset();

public:
  explicit Cat() : Agent(){};
  Point2D Move(CatWorld*) override;
};

#endif  // CAT_H
