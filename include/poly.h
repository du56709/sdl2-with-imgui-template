#pragma once

struct Point3D
{
	float x, y, z;
};

struct Triangle3D
{
	Point3D p[3];
};

// pnpoly - need to include licence...
// https://wrfranklin.org/Research/Short_Notes/pnpoly.html
bool pnpoly(Triangle3D * t, Point3D * p);

float weightedAverage(float w1, float c1, float w2, float c2, float w3, float c3);
float getInterpolatedFromPoint(Point3D * p, Triangle3D * t);
