#include "1.h"

#include <iostream>
#include<algorithm>

DayOne::DayOne(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayOne::runChallange()
{
	std::string line;

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		char first = *std::find_if(line.begin(), line.end(), isdigit);
		char last = *std::find_if(line.rbegin(), line.rend(), isdigit);

		std::string strResult{ first, last };

		result += std::stoi(strResult);
	}

	return std::to_string(result);
}

std::vector<std::string> stringNumbers{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int numberFound(const std::string& s, bool reverse)
{
	char lastAddedChar = s.back();
	if (isdigit(lastAddedChar)) // Latest added char
	{
		return s.back() - '0';
	}

	auto ptr = std::find_if(stringNumbers.begin(), stringNumbers.end(), [&s, &reverse](std::string number)
		{
			if (reverse)
			{
				std::reverse(number.begin(), number.end());
			}

			return s.find(number) != std::string::npos;
		});

	if (ptr != stringNumbers.end())
	{
		return int(ptr - stringNumbers.begin()) + 1;
	}

	return -1;
}

template<typename iteratorT>
int findFirstNumber(iteratorT begin, iteratorT end, bool reverse = false)
{
	auto keepFirst = begin;

	while (begin != end)
	{
		std::advance(begin, 1);

		std::string currentString{ keepFirst, begin };

		int res = numberFound(currentString, reverse);

		if (res != -1)
		{
			return res;
		}
	}
}

std::string DayOne::runChallangePart2()
{
	std::string line;

	int res = 0;

	while (std::getline(inputManager->file, line))
	{
		auto f = findFirstNumber(line.begin(), line.end());

		std::reverse(line.begin(), line.end());

		auto l = findFirstNumber(line.begin(), line.end(), true);

		res += f * 10 + l;
	}

	return std::to_string(res);
}