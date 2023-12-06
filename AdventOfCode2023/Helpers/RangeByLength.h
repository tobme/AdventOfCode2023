#pragma once

template<typename T>
class RangeByLength
{
public:
	RangeByLength(T s, unsigned long l);

	T getStartValue() const;
	unsigned long getLength() const;
private:
	T start;
	unsigned long length;
};

template<typename T>
RangeByLength<T> findIntersection(const RangeByLength<T>& a1, const RangeByLength<T>& a2);
