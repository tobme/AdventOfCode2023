#pragma once

class Point
{
public:
	Point(int _x, int _y);

	double distance(const Point& p);

	int x;
	int y;
};