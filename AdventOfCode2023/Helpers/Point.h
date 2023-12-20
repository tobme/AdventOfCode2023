#pragma once
#include <cstddef>
#include <functional>

class Point
{
public:
	Point() = default;

	Point(int _x, int _y);

	double pythDistance(const Point& p);

	int distance(const Point& p);

	Point operator+(const Point & p);

	bool operator==(const Point& p) const;

	int x;
	int y;
};

struct PointHashFunction
{
	std::size_t operator()(const Point& p) const
	{
		size_t rowHash = std::hash<int>()(p.x);
		size_t colHash = std::hash<int>()(p.y) << 1;
		return rowHash ^ colHash;
	}
};