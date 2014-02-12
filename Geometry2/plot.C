#include "plot.h"

int window1;

void graphics_init (int argc, char **argv, int wsize, int linewidth, 
		    float pointsize)
{
  glutInit(&argc, argv);
  glutInitWindowSize(wsize, wsize);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  window1 = glutCreateWindow("");
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutDisplayFunc(display);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  graphics_init_aux();
  glLineWidth(linewidth);
  glPointSize(pointsize);
  menu_init();
  Parameter::enable();
  glutMainLoop();
}

void mouse_generic (int button, int buttonState, int x, int y,
		    Points &inpoints)
{
  static Point *oldp = 0;
  if (button == GLUT_LEFT_BUTTON && buttonState == GLUT_UP)
    return;
  Point *p = point(x, y);
  if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
    remove_point(p, inpoints);
    delete p;
  }
  else if (button == GLUT_LEFT_BUTTON)
    inpoints.push_back(p);
  else if (buttonState == GLUT_DOWN) {
    delete oldp;
    oldp = p;
  }
  else {
    int i = closest_point(oldp, inpoints);
    if (i == -1) 
      delete p;
    else {
      delete inpoints[i];
      inpoints[i] = p;
    }
  }
}

void reshape (int w, int h)
{
  glViewport(0, 0, w, h);
}

Point * point (int x, int y)
{
  double u = x/(double) glutGet(GLUT_WINDOW_WIDTH),
    v = 1.0 - y/(double) glutGet(GLUT_WINDOW_HEIGHT),
    s = 2.0*u - 1.0, t = 2.0*v - 1.0;
  return new InputPoint(s, t);
}

void clear_screen (float *color)
{
  glClearColor(color[0], color[1], color[2], color[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void draw_points (const Points &points)
{
  glBegin(GL_POINTS);
  for (int i = 0; i < points.size(); ++i)
    glVertex(points[i]);
  glEnd();
}

void draw_lines (const Points &pts)
{
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i < pts.size(); ++i)
    glVertex(pts[i]);
  glEnd();
}

void draw_loop (const Points &pts)
{
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < pts.size(); ++i)
    glVertex(pts[i]);
  glEnd();
}

void draw_line (Point *t, Point *h)
{
  glBegin(GL_LINES);
  glVertex(t);
  glVertex(h);
  glEnd();
}

void draw_triangle (Point *a, Point *b, Point *c)
{
  glBegin(GL_TRIANGLES);
  glVertex(a);
  glVertex(b);
  glVertex(c);
  glEnd();
}

void draw_box (Point *bl, Point *tr)
{
  glBegin(GL_LINE_LOOP);
  glVertex(bl);
  glVertex2d(tr->getP().x.mid(), bl->getP().y.mid());
  glVertex(tr);
  glVertex2d(bl->getP().x.mid(), tr->getP().y.mid());
  glEnd();
}

void glVertex (Point *p)
{
  glVertex2d(p->getP().x.mid(), p->getP().y.mid());
}

void remove_point (Point *p, Points &pts)
{
  int i = closest_point(p, pts);
  if (i == -1)
    return;
  delete pts[i];
  pts[i] = *(pts.end()-1);
  pts.pop_back();
}

int closest_point (Point *p, Points &pts)
{
  if (pts.empty())
    return -1;
  Parameter d = distanceSquared(p, pts[0]);
  int nd = 0;
  for (int i = 1; i < pts.size(); ++i) {
    Parameter di = distanceSquared(p, pts[i]);
    if (di < d) {
      d = di;
      nd = i;
    }
  }
  return nd;
}

double distanceSquared (Point *a, Point *b)
{
  PV2 u = a->getP() - b->getP();
  return u.dot(u).mid();
}

void clear_points (Points &pts)
{
  for (Points::iterator p = pts.begin(); p != pts.end(); ++p)
    delete *p;
  pts.clear();
}

void read_points (Points &inpoints)
{
  cerr << "Enter filename: ";
  string name;
  cin >> name;
  ifstream istr(name.c_str());
  if (!istr.good()) return;
  clear_points(inpoints);
  readPoints(istr, inpoints);
}

void readPoints (istream &istr, Points &pts)
{
  int n;
  istr >> n;
  for (int i = 0; i < n; ++i) {
  double x, y;
  istr >> x >> y;
  pts.push_back(new InputPoint(x, y));
  }
}

void writePoints (ostream &ostr, const Points &pts)
{
  ostr << pts.size() << endl;
  for (Points::const_iterator p = pts.begin(); p != pts.end(); ++p)
    ostr << (*p)->getP().x.mid() << " " << (*p)->getP().y.mid() << endl;
}

int main (int argc, char **argv)
{
  int wsize = 500;
  int linewidth = 1;
  float pointsize = 5.0f;
  graphics_init(argc, argv, wsize, linewidth, pointsize);
  return 0;
}
