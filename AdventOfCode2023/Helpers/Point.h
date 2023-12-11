#pragma once

class Point
{
public:
	Point(int _x, int _y);

	double pythDistance(const Point& p);

	int distance(const Point& p);

	int x;
	int y;
};