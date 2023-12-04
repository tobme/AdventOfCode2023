#include "4.h"

#include <iostream>
#include<sstream>
#include<unordered_set>
#include<unordered_map>

DayFour::DayFour(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayFour::runChallange()
{
	std::string line;
	std::string word;

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		std::unordered_set<int> winningNumbers;

		ss << line;
		ss >> word;
		ss >> word;

		ss >> word;

		while (word != "|")
		{
			winningNumbers.insert(std::stoi(word));
			ss >> word;
		}

		int matches = 0;

		while (ss >> word)
		{
			int number = std::stoi(word);
			if (winningNumbers.contains(number))
			{
				matches++;
			}
		}
		result += pow(2, matches - 1);
	}
	return std::to_string(result);
}

std::unordered_map<int, int> memory{};

int findMatches(const std::vector<std::pair<int, int>>& cards, const std::pair<int,int>& requestedCard)
{
	int cardNumber = requestedCard.first;
	int result = 1;

	if (memory.contains(cardNumber))
	{
		return memory[cardNumber];
	}

	for (int i = 0; i < requestedCard.second; i++)
	{
		auto findMatchFor = cards.at(cardNumber + i);
		result += findMatches(cards, findMatchFor);
	}

	memory[cardNumber] = result;
	return result;
}

std::string DayFour::runChallangePart2()
{
	std::string line;
	std::string word;

	int result = 0;

	std::vector<std::pair<int, int>> cards;

	inputManager->file.clear();
	inputManager->file.seekg(0);

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		std::unordered_set<int> winningNumbers;

		ss << line;
		ss >> word;
		ss >> word;
		word.pop_back();
		int cardNumber = std::stoi(word);

		ss >> word;

		while (word != "|")
		{
			winningNumbers.insert(std::stoi(word));
			ss >> word;
		}

		int matches = 0;

		while (ss >> word)
		{
			int number = std::stoi(word);
			if (winningNumbers.contains(number))
			{
				matches++;
			}
		}
		cards.push_back(std::pair<int, int>(cardNumber, matches));
	}

	for (auto it = cards.begin(); it != cards.end(); ++it)
	{
		result += findMatches(cards, *it);
	}

	return std::to_string(result);
}