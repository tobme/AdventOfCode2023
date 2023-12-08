#include "8.h"

#include <iostream>
#include<sstream>
#include<unordered_map>
#include <algorithm>
#include <numeric>

DayEight::DayEight(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayEight::runChallange()
{
	std::string instructions;

	std::getline(inputManager->file, instructions);

	std::string line;

	std::getline(inputManager->file, line); // Skip empty line

	std::unordered_map<std::string, std::pair<std::string, std::string>> network;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;

		std::string base;
		ss >> base;

		ss >> line; // skip

		std::string left;
		ss >> left;
		left.pop_back();
		left.erase(0, 1);

		std::string right;
		ss >> right;
		right.pop_back();

		network[base] = std::pair<std::string, std::string>(left, right);
	}

	std::string position = "AAA";
	int steps = 0;

	auto it = instructions.begin();

	while (position != "ZZZ")
	{
		if (*it == 'L')
		{
			position = network[position].first;
		}
		else
		{
			position = network[position].second;
		}
		steps++;

		if ((++it) == instructions.end())
			it = instructions.begin();
	}

	return std::to_string(steps);
}

std::string DayEight::runChallangePart2()
{
	inputManager->resetStream();

	std::string instructions;

	std::getline(inputManager->file, instructions);

	std::string line;

	std::getline(inputManager->file, line); // Skip empty line

	std::unordered_map<std::string, std::pair<std::string, std::string>> network;

	std::vector<std::string> startingPositions;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;

		std::string base;
		ss >> base;

		ss >> line; // skip

		std::string left;
		ss >> left;
		left.pop_back();
		left.erase(0, 1);

		std::string right;
		ss >> right;
		right.pop_back();

		network[base] = std::pair<std::string, std::string>(left, right);
		if (base.back() == 'A')
			startingPositions.push_back(base);
	}

	std::vector<int> results;

	for (std::string& pos : startingPositions)
	{
		auto it = instructions.begin();
		int steps = 0;

		while (pos.back() != 'Z')
		{
			if (*it == 'L')
			{
				pos = network[pos].first;
			}
			else
			{
				pos = network[pos].second;
			}

			steps++;

			if ((++it) == instructions.end())
				it = instructions.begin();
		}
		results.push_back(steps);
	}

	std::sort(results.begin(), results.end());

	unsigned long long lcm = results.back();
	results.pop_back();

	for (auto res : results)
	{
		lcm = lcm * res / std::gcd(lcm, res);
	}

	return std::to_string(lcm);
}