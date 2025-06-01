#include "poly.h"

// pnpoly - need to include licence...
// https://wrfranklin.org/Research/Short_Notes/pnpoly.html
bool pnpoly(Triangle3D * t, Point3D * p)
{
	int nvert = 3;
	float vertx[3] = {t->p[0].x, t->p[1].x, t->p[2].x};
	float verty[3] = {t->p[0].y, t->p[1].y, t->p[2].y};
	
	float testx = p->x;
	float testy = p->y;
	
	int i, j;
	bool c = false;
	for (i = 0, j = nvert-1; i < nvert; j = i++) {
		if(((verty[i]>testy) != (verty[j]>testy)) && (testx < (vertx[j]-vertx[i]) * (testy-verty[i]) / (verty[j]-verty[i]) + vertx[i]))
		{
			c = !c;
		}
	}
	
	return c;
}

float weightedAverage(float w1, float c1, float w2, float c2, float w3, float c3)
{
	return ((w1 * c1) + (w2 * c2) + (w3 * c3)) / (w1 + w2 + w3);
}


// I'm sure there's another way of doing this
float getInterpolatedPoint(Point3D * p, Triangle3D * t)
{
	float w1, w2, w3;
	
	// https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Edge_approach
	w1 = (((t->p[1].y - t->p[2].y) * (p->x - t->p[2].x)) + ((t->p[2].x - t->p[1].x) * (p->y - t->p[2].y))) 
	   / (((t->p[1].y - t->p[2].y) * (t->p[0].x - t->p[2].x)) + ((t->p[2].x - t->p[1].x) * (t->p[0].y - t->p[2].y)));
	
	w2 = (((t->p[2].y - t->p[0].y) * (p->x - t->p[2].x)) + ((t->p[0].x - t->p[2].x) * (p->y - t->p[2].y))) 
	   / (((t->p[1].y - t->p[2].y) * (t->p[0].x - t->p[2].x)) + ((t->p[2].x - t->p[1].x) * (t->p[0].y - t->p[2].y)));
	
	w3 = 1 - w1 - w2;
	
	return weightedAverage(w1, t->p[0].z, w2, t->p[1].z, w3, t->p[2].z);
}
