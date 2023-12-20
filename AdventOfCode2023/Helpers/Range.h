#pragma once

template<typename T>
class Range
{
public:
	Range() = default;
	Range(T s, T e);

	T start;
	T end;

	T getLength() const;
};

template<typename T>
Range<T> findIntersection(const Range<T>& r1, const Range<T>& r2);