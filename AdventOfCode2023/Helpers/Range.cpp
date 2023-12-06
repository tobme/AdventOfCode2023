#include "Range.h"

#include<math.h>

template<typename T>
Range<T>::Range(T s, T e) : start(s), end(e) {}

template<typename T>
T Range<T>::getLength() const
{
	return abs(end - start);
}

template<typename T>
Range<T> findIntersection(const Range<T>& r1, const Range<T>& r2)
{
	T interSectionStart = max(r1.start, r2.start);

	T interSectionEnd = min(r1.end, r2.end);

	T interSectionRange = interSectionEnd - interSectionStart;

	return Range<T>(interSectionStart, interSectionRange);
}

template class Range<int>;
template class Range<unsigned int>;