#include "6.h"

#include <iostream>
#include<sstream>
#include<vector>

DaySix::DaySix(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DaySix::runChallange()
{
	std::string line;

	std::getline(inputManager->file, line);

	std::stringstream ss;

	ss << line;

	std::string word;

	ss >> word;

	std::vector<int> times;

	while (ss >> word)
	{
		times.push_back(std::stoi(word));
	}

	std::getline(inputManager->file, line);

	ss = std::stringstream{};

	ss << line;

	ss >> word;

	std::vector<int> distance;

	while (ss >> word)
	{
		distance.push_back(std::stoi(word));
	}

	int result = 1;

	for (int i = 0; i < times.size(); i++)
	{
		int beatRaceTime = 0;

		for (int holdTime = 1; holdTime < times.at(i); holdTime++)
		{
			int travelTime = times.at(i) - holdTime;

			int travelDistance = travelTime * holdTime;

			if (travelDistance > distance.at(i))
			{
				beatRaceTime++;
			}
		}

		result *= beatRaceTime;
	}

	return std::to_string(result);
}

std::string DaySix::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	std::getline(inputManager->file, line);

	std::stringstream ss;

	ss << line;

	std::string word;

	ss >> word;

	std::string sTime = "";

	while (ss >> word)
	{
		sTime += word;
	}

	unsigned long long time = std::stoull(sTime);

	std::getline(inputManager->file, line);

	ss = std::stringstream{};

	ss << line;

	ss >> word;

	std::string sDistance = "";

	while (ss >> word)
	{
		sDistance += word;
	}

	unsigned long long distance = std::stoull(sDistance);

	unsigned long long beatRaceTime = 0;

	for (unsigned long long holdTime = 1; holdTime < time; holdTime++)
	{
		unsigned long long travelTime = time - holdTime;

		unsigned long long travelDistance = travelTime * holdTime;

		if (travelDistance > distance)
		{
			beatRaceTime++;
		}
	}

	return std::to_string(beatRaceTime);
}