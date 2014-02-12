#include <vector>
#include <iostream>
#include "point.h"
#include "arrange.h"

using namespace std;

int main(int argc, char *argv[]) {
	Arrangement a(true);
	Arrangement b(true);

	Point* p1 = new InputPoint(0, 0);
	Point* p2 = new InputPoint(10, 0);
	Point* p3 = new InputPoint(5, 7);
	Vertex* v1 = a.addVertex(p1);
	Vertex* v2 = a.addVertex(p2);
	Vertex* v3 = a.addVertex(p3);
	a.addEdge(v1, v2);
	a.addEdge(v2, v3);
	a.addEdge(v3, v1);

	Point* p4 = new InputPoint(-5, 3);
	Point* p5 = new InputPoint(5, 3);
	Point* p6 = new InputPoint(0, 10);
	Vertex* v4 = b.addVertex(p4);
	Vertex* v5 = b.addVertex(p5);
	Vertex* v6 = b.addVertex(p6);
	b.addEdge(v4, v5);
	b.addEdge(v5, v6);
	b.addEdge(v6, v4);


	Arrangement* o = overlay(&a, &b);

	std::cout << "Vertices: " << o->vertices.size() << std::endl;
	std::cout << "Edges: " << o->edges.size() << std::endl;
	std::cout << "Faces: " << o->faces.size() << std::endl;

	for (int i = 0; i < o->vertices.size(); ++i) {
		std::cout << "Point [" << i << "]: " << o->vertices[i]->p->getP().getX().mid() << "," << o->vertices[i]->p->getP().getY().mid() << std::endl;
	}

	/*
	for (int i = 0; i < o->edges.size(); ++i) {
		std::cout << "(" << o->edges[i]->tail->p->getP().getX().mid() << "," << o->edges[i]->tail->p->getP().getY().mid() << ") -> (" << o->edges[i]->head()->p->getP().getX().mid() << "," << o->edges[i]->head()->p->getP().getY().mid() << ")" << std::endl;
	}
	*/

	return 0;
}
