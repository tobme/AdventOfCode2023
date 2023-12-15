#include "15.h"

#include <iostream>
#include<unordered_map>

DayFifteen::DayFifteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayFifteen::runChallange()
{
	char c;

	unsigned long long result = 0;
	unsigned long long currentResult = 0;

	while(inputManager->file.get(c))
	{
		if (c != ',')
		{
			currentResult += c;
			currentResult *= 17;
			currentResult = currentResult % 256;
		}
		else
		{
			result += currentResult;
			currentResult = 0;
		}
	}
	result += currentResult;

	return std::to_string(result);
}

class Lens
{
public:
	Lens(const std::string& _id, int _f) : id(_id), focalLength(_f) {}

	bool operator==(const Lens& r)
	{
		return id == r.id;
	}

	std::string id;
	int focalLength;
};

int calcResult(const std::unordered_map<int, std::vector<Lens*>>& boxes)
{
	int result = 0;
	for (auto& box : boxes)
	{
		for (int i = 0; i < box.second.size(); i++)
		{
			result += (box.first + 1) * (i + 1) * box.second.at(i)->focalLength;
		}
	}
	return result;
}

std::string DayFifteen::runChallangePart2()
{
	inputManager->resetStream();

	char c;

	unsigned long long result = 0;
	unsigned long long currentResult = 0;
	std::string currentID = "";

	std::unordered_map<int, std::vector<Lens*>> boxes{};

	while (inputManager->file.get(c))
	{
		if (c == '=')
		{
			inputManager->file.get(c);

			auto& lenses = boxes[currentResult];
			int focalLength = c - '0';

			auto it = std::find_if(lenses.begin(), lenses.end(), [&currentID](const auto& lens)
				{
					return lens->id == currentID;
				});

			if (it != lenses.end())
			{
				(*it)->focalLength = focalLength;
			}
			else
			{
				lenses.push_back(new Lens(currentID, focalLength));
			}

			currentResult = 0;
			currentID = "";
		}
		else if (c == '-')
		{
			auto& lenses = boxes[currentResult];

			auto it = std::find_if(lenses.begin(), lenses.end(), [&currentID](const auto& lens)
				{
					return lens->id == currentID;
				});

			if (it != lenses.end())
			{
				lenses.erase(it, it + 1);
			}

			currentResult = 0;
			currentID = "";
		}
		else if (c != ',')
		{
			currentID += c;
			currentResult += c;
			currentResult *= 17;
			currentResult = currentResult % 256;
		}
	}

	result = calcResult(boxes);

	for (auto& t : boxes)
	{
		for (auto& p : t.second)
		{
			free(p);
		}
	}

	return std::to_string(result);
}