#include "9.h"

#include <iostream>
#include<sstream>

DayNine::DayNine(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

long long int findHistoryValue(const std::vector<long long int>& diffs)
{
	auto it = std::find_if(diffs.begin(), diffs.end(), [](auto v)
		{
			return v != 0;
		});


	if (it == diffs.end())
		return 0;

	std::vector<long long int> newDiffs;
	for (int i = 0; i < diffs.size() - 1; i++)
	{
		long long int tmpDiff = diffs.at(i + 1) - diffs.at(i);
		newDiffs.push_back(tmpDiff);
	}

	return diffs.back() + findHistoryValue(newDiffs);
}

std::string DayNine::runChallange()
{
	std::string line;
	long long int number;
	long long int result = 0;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;

		std::vector<long long int> numbers;

		while (ss >> number)
		{
			numbers.push_back(number);
		}

		result += findHistoryValue(numbers);
	}

	return std::to_string(result);
}

long long int findHistoryValue2(const std::vector<long long int>& diffs)
{
	auto it = std::find_if(diffs.begin(), diffs.end(), [](auto v)
		{
			return v != 0;
		});


	if (it == diffs.end())
		return 0;

	std::vector<long long int> newDiffs;
	for (int i = 0; i < diffs.size() - 1; i++)
	{
		long long int tmpDiff = diffs.at(i + 1) - diffs.at(i);
		newDiffs.push_back(tmpDiff);
	}

	auto s = diffs.front() - findHistoryValue2(newDiffs);
	return s;
}

std::string DayNine::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;
	long long int number;
	long long int result = 0;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;

		std::vector<long long int> numbers;

		while (ss >> number)
		{
			numbers.push_back(number);
		}

		result += findHistoryValue2(numbers);
	}

	return std::to_string(result);
}