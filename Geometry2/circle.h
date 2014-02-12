#ifndef CIRCLE
#define CIRCLE

#include "point.h"

class Circle : public Object {
 private:
  Parameters getParameters () { return Parameters(rr, o); }
 protected:
  PV2 o;
  Parameter rr;
 public:
  PV2 getO () { return o; }
  Parameter getRR () { return rr; }
  bool contains (Point *p);
};

class Circle2pts : public Circle {
 private:
  Objects getObjects () { return Objects(a, b); }
  void calculate () {
    o = 0.5*(a->getP() + b->getP());
    PV2 u = o - a->getP();
    rr = u.dot(u);
  }
  Point *a, *b;
 public:
  Circle2pts (Point *a, Point *b) : a(a), b(b) { calculate(); }
};

class Circle3pts : public Circle {
 private:
  Objects getObjects () { return Objects(a, b, c); }
  void calculate () {
    o = circumCenter(a->getP(), b->getP(), c->getP());
    PV2 u = o - a->getP();
    rr = u.dot(u);
  }
  Point *a, *b, *c;
 public:
  Circle3pts (Point *a, Point *b, Point *c) : a(a), b(b), c(c)
  { calculate(); }
};

Predicate2(PointInCircle, Point *, p, Circle *, c);

#endif
