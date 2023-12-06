#include "5.h"

#include <iostream>
#include<sstream>
#include<unordered_map>
#include<set>
#include <algorithm>

DayFive::DayFive(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

struct Mapper
{
	unsigned long long sourceStart;
	unsigned long long destinationStart;
	unsigned long long length;
};

std::string DayFive::runChallange()
{
	
	std::string line;
	std::string word;

	std::getline(inputManager->file, line);
	std::stringstream ss;
	ss << line;

	ss >> word;

	std::vector<unsigned long long> lastResults;

	while (ss >> word)
	{
		lastResults.push_back(std::stoull(word));
	}

	std::vector<Mapper> map;

	std::getline(inputManager->file, line); // Skip first
	std::getline(inputManager->file, line); // Skip first

	while (std::getline(inputManager->file, line))
	{
		if (line.find("map:") == std::string::npos && line != "")
		{
			std::stringstream sss;
			sss << line;

			unsigned long long destination, source, length;
			sss >> destination;
			sss >> source;
			sss >> length;

			Mapper mapper;
			mapper.sourceStart = source;
			mapper.destinationStart = destination;
			mapper.length = length;

			map.push_back(mapper);
		}
		else if (line != "")
		{
			std::vector<unsigned long long> newResults;
			bool found = false;
			for (unsigned long long r : lastResults)
			{
				for (const Mapper& mapper : map)
				{
					if (mapper.sourceStart <= r && r < mapper.sourceStart + mapper.length)
					{
						unsigned long long source = mapper.destinationStart + (r - mapper.sourceStart);
						newResults.push_back(source);
						found = true;
						break;
					}
				}
				if (!found)
				{
					newResults.push_back(r);
				}
				found = false;
			}
			lastResults = newResults;

			map = std::vector<Mapper>();
		}
	}

	unsigned long long minResult = *std::min_element(lastResults.begin(), lastResults.end());

	return std::to_string(minResult);
}

struct pairComparer
{
	bool operator()(const std::pair<unsigned long long, unsigned long long>& a1, const std::pair<unsigned long long, unsigned long long>& a2) const
	{
		return a1.first < a2.first;
	}
};

std::string DayFive::runChallangePart2()
{
	inputManager->file.clear();
	inputManager->file.seekg(0);

	std::string line;
	std::string word;

	std::getline(inputManager->file, line);
	std::stringstream ss;
	ss << line;

	ss >> word;
	std::string slength;

	std::vector<std::pair<unsigned long long, unsigned long long>> lastResults;

	while (ss >> word)
	{
		ss >> slength;
		unsigned long long seedStart = std::stoull(word);
		unsigned long long length = std::stoull(slength);
		lastResults.push_back(std::pair<unsigned long long, unsigned long long>(seedStart, length));
	}

	std::vector<Mapper> map;

	std::getline(inputManager->file, line); // Skip first
	std::getline(inputManager->file, line); // Skip first

	while (std::getline(inputManager->file, line))
	{
		if (line.find("map:") == std::string::npos && line != "")
		{
			std::stringstream sss;
			sss << line;

			unsigned long long destination, source, length;
			sss >> destination;
			sss >> source;
			sss >> length;

			Mapper mapper;
			mapper.sourceStart = source;
			mapper.destinationStart = destination;
			mapper.length = length;

			map.push_back(mapper);
		}
		else if (line != "")
		{
			std::vector<std::pair<unsigned long long, unsigned long long>> newResults;
			bool found = false;
			for (auto& r : lastResults)
			{
				std::set<std::pair<unsigned long long, unsigned long long>, pairComparer> translatedPair;
				for (Mapper& mapper : map)
				{

					if (mapper.sourceStart + mapper.length >= r.first && mapper.sourceStart <= r.first + r.second)
					{
						// Find new range
						unsigned long long intersectionRangeStart = std::max(r.first, mapper.sourceStart);
						unsigned long long intersectionRangeEnd = std::min(r.first + r.second, mapper.sourceStart + mapper.length);

						unsigned long long intersectionLength = intersectionRangeEnd - intersectionRangeStart;

						unsigned long long destinationValue = mapper.destinationStart + (intersectionRangeStart - mapper.sourceStart);

						newResults.push_back(std::pair<unsigned long long, unsigned long long>(destinationValue, intersectionLength));
						translatedPair.insert(std::pair<unsigned long long, unsigned long long>(intersectionRangeStart, intersectionLength));
					}
				}

				unsigned long long startValue = r.first;

				for (auto& s : translatedPair)
				{
					if (startValue < s.first)
					{
						unsigned long long length = s.first - startValue;
						newResults.push_back(std::pair<unsigned long long, unsigned long long>(startValue, length));
					}
					startValue = s.first + s.second;
				}

				if ((startValue < r.first + r.second && startValue != r.first) || translatedPair.size() == 0)
				{
					unsigned long long length = (r.first + r.second) - startValue;
					newResults.push_back(std::pair<unsigned long long, unsigned long long>(startValue, length));
				}
			}

			lastResults = newResults;

			map = std::vector<Mapper>();
		}
	}

	auto minResult = std::min_element(lastResults.begin(), lastResults.end(), pairComparer());

	return std::to_string(minResult->first);
}