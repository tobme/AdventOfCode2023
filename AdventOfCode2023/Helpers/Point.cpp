#include "Point.h"

#include<math.h>


Point::Point(int _x, int _y) : x(_x), y(_y)
{
}

double Point::pythDistance(const Point& p)
{
	int xDist = abs(x - p.x);
	int yDist = abs(y - p.y);

	double dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

	return dist;
}

int Point::distance(const Point& p)
{
	int xDist = abs(x - p.x);
	int yDist = abs(y - p.y);

	return xDist + yDist;
}

Point Point::operator+(const Point& p)
{
	int tx = x + p.x;
	int ty = y + p.y;
	return Point(tx, ty);
}

bool Point::operator==(const Point& p) const
{
	return x == p.x && y == p.y;
}
