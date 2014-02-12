#include "circle.h"

bool Circle::contains (Point *p)
{
  return PointInCircle(p, this) == 1; 
}

int PointInCircle::sign ()
{
  PV2 u = p->getP() - c->getO();
  return (c->getRR() - u.dot(u)).sign();
}
