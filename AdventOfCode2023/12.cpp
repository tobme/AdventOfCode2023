#include "12.h"

#include <iostream>
#include<sstream>
#include<queue>
#include<unordered_map>

DayTwelve::DayTwelve(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

unsigned long long findNextDamage(const std::string& springs, unsigned long long i = 0)
{
	if (i > springs.size())
		return 999999;

	unsigned long long t = springs.substr(i).find_first_of("#?");

	return t != std::string::npos ? t + i : 999999;
}

std::unordered_map<std::string, unsigned long long> memory2{};

unsigned long long solution(const std::string& springs, std::vector<int> numbers, unsigned long long index)
{
	std::string ID = springs;

	ID += "-";

	for (int i : numbers)
		ID += std::to_string(i);

	ID += "-";

	ID += std::to_string(index);

	if (memory2.contains(ID))
		return memory2[ID];

	unsigned long long result = 0;

	for (unsigned long long i = index; i + numbers.front() - 1 < springs.size(); i = findNextDamage(springs, i))
	{
		if (springs.substr(i, numbers.front()).find('.') == std::string::npos)
		{
			if (springs[i] != '#') // If standing on a damage, then it wont work to not include it
			{
				result += solution(springs, numbers, findNextDamage(springs, i+1));
			}

			i += numbers.front();
			numbers.erase(numbers.begin(), numbers.begin() + 1);

			if (numbers.size() == 0)
			{
				if (springs.substr(i).find('#') == std::string::npos) // Check if remainder has a #
					result++;
				break;
			}

			if (i < springs.size() && springs[i] == '#') // Cant skip damaged
				break;

			i++;
		}
		else if (springs[i] == '#') // if standing on a damage but it's not long enough for numbers, then its not good =)
		{
			break;
		}
		else
		{
			i++;
		}
	}

	memory2[ID] = result;

	return result;
}

std::string DayTwelve::runChallange()
{
	std::string line;
	std::string springs;
	std::string number;

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		std::vector<int> numbers;
		std::stringstream ss;
		ss << line;

		ss >> springs;
		ss >> number;
		size_t pos;
		while ((pos = number.find(",")) != std::string::npos)
		{
			std::string tmp = number.substr(0, pos);
			numbers.push_back(std::stoi(tmp));
			number.erase(0, pos + 1);
		}
		numbers.push_back(std::stoi(number));

		memory2 = std::unordered_map<std::string, unsigned long long>(); // reset memory

		int tmp = solution(springs, numbers, findNextDamage(springs));
		result += tmp;
	}
	return std::to_string(result);
}

std::string DayTwelve::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;
	std::string springs;
	std::string number;

	unsigned long long result = 0;

	while (std::getline(inputManager->file, line))
	{
		std::vector<int> numbers;
		std::stringstream ss;
		ss << line;

		ss >> springs;
		ss >> number;

		number = number + "," + number + "," + number + "," + number + "," + number;

		size_t pos;
		while ((pos = number.find(",")) != std::string::npos)
		{
			std::string tmp = number.substr(0, pos);
			numbers.push_back(std::stoi(tmp));
			number.erase(0, pos + 1);
		}
		numbers.push_back(std::stoi(number));

		springs = springs + "?" + springs + "?" + springs + "?" + springs + "?" + springs;

		memory2 = std::unordered_map<std::string, unsigned long long>(); // reset memory

		unsigned long long tmp = solution(springs, numbers, findNextDamage(springs));
		result += tmp;
	}
	return std::to_string(result);
}