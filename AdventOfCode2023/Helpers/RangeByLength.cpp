#include "RangeByLength.h"

template<typename T>
RangeByLength<T>::RangeByLength(T s, unsigned long l) : start(s), length(l)
{
}

template<typename T>
T RangeByLength<T>::getStartValue() const
{
	return start;
}

template<typename T>
unsigned long RangeByLength<T>::getLength() const
{
	return length;
}

template<typename T>
RangeByLength<T> findIntersection(const RangeByLength<T>& a1, const RangeByLength<T>& a2)
{
	T interSectionStart = max(a1.getStartValue(), a2.getStartValue());

	T a1End = a1.getStartValue() + a1.getLength();
	T a2End = a2.getStartValue() + a2.getLength();

	T interSectionEnd = min(a1End, a2End);

	T interSectionRange = interSectionEnd - interSectionStart;

	return RangeByLength<T>(interSectionStart, interSectionRange);
}

template class RangeByLength<int>;