#ifndef	PLOT
#define PLOT

#include <GL/glut.h>
#include <fstream>
#include "point.h"

void graphics_init (int argc, char **argv, int wsize, int linewidth, 
		    float pointsize);

void graphics_init_aux ();

void menu_init ();

void menu (int value);

void mouse (int button, int buttonState, int x, int y);

void mouse_generic (int button, int buttonState, int x, int y,
		    Points &inpoints);

void reshape (int w, int h);

Point * point (int x, int y);

void display ();

void clear_screen (float *color);

void draw_points (const Points &pts);

void draw_lines (const Points &pts);

void draw_loop (const Points &pts);

void draw_line (Point *t, Point *h);

void draw_triangle (Point *a, Point *b, Point *c);

void draw_box (Point *bl, Point *tr);

void glVertex (Point *p);

void remove_point (Point *p, Points &pts);

int closest_point (Point *p, Points &pts);

double distanceSquared (Point *a, Point *b);

void clear_points (Points &pts);

void read_points (Points &inpoints);

void readPoints (istream &istr, Points &pts);

void writePoints (ostream &ostr, const Points &pts);

#endif
