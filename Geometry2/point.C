#include "point.h"

int XSign::sign ()
{
  return a->getP().x.sign();
}

int YSign::sign ()
{
  return a->getP().y.sign();
}

int XOrder::sign ()
{
  return (b->getP().x - a->getP().x).sign();
}

int YOrder::sign ()
{
  return (b->getP().y - a->getP().y).sign();
}

int NormOrder::sign ()
{
  return (b->getP().dot(b->getP()) - a->getP().dot(a->getP())).sign();
}

int CCW::sign ()
{
  return a->getP().cross(b->getP()).sign();
}

int LeftTurn::sign ()
{
  return (c->getP() - b->getP()).cross(a->getP() - b->getP()).sign();
}

int PointInCircumcircle::sign ()
{
  const PV2 &pp = p->getP(), &pa = a->getP(), &pb = b->getP(), &pc = c->getP();
  Parameter a1 = pa.x - pp.x, a2 = pa.y - pp.y, a3 = a1*a1 + a2*a2;
  Parameter b1 = pb.x - pp.x, b2 = pb.y - pp.y, b3 = b1*b1 + b2*b2;
  Parameter c1 = pc.x - pp.x, c2 = pc.y - pp.y, c3 = c1*c1 + c2*c2;
  Parameter k = a1*(b2*c3-b3*c2) - a2*(b1*c3-b3*c1) + a3*(b1*c2-b2*c1);
  return k.sign();
}

PV2 lineIntersection (const PV2 &a, const PV2 &b, const PV2 &c, const PV2 &d)
{
  PV2 u = b - a, v = d - c;
  Parameter k = (c - a).cross(v)/u.cross(v);
  return a + k*u;
}

PV2 circumCenter (const PV2 &a, const PV2 &b, const PV2 &c)
{
  Parameter xy[2];
  linsolve2(a.y - b.y, c.y - a.y, b.x - a.x, a.x - c.x, 
	    0.5*(c.x - b.x), 0.5*(c.y - b.y), xy);
  return PV2(0.5*(a.x + b.x) + xy[0]*(a.y - b.y),
	     0.5*(a.y + b.y) + xy[0]*(b.x - a.x));
}

void linsolve2 (Parameter a, Parameter b, Parameter c, Parameter d, 
		Parameter e, Parameter f, Parameter *xy)
{
  Parameter den = a*d - b*c;
  xy[0] = (e*d - b*f)/den;
  xy[1] = (a*f - c*e)/den;
}

void pp (Point *p)
{
  PV2 pp = p->getP();
  cerr << setprecision(16) << "(" << pp.x.mid() << " " 
       << pp.y.mid() << ")" << endl;
}
