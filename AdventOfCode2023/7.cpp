#include "7.h"

#include <iostream>
#include<sstream>
#include<unordered_map>
#include <algorithm>

DaySeven::DaySeven(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

enum class CardStrength : unsigned int
{
	High_Card = 1,
	One_Pair = 2,
	Two_Pair = 3,
	Three_of_Kind = 4,
	Full_House = 5,
	Four_of_Kind = 6,
	Five_of_Kind = 7
};

int translateCardValue(char c)
{
	if (isdigit(c))
	{
		return c - '0';
	}
	else if (c == 'T')
	{
		return 10;
	}
	else if (c == 'J')
	{
		return 11;
	}
	else if (c == 'Q')
	{
		return 12;
	}
	else if (c == 'K')
	{
		return 13;
	}
	else if (c == 'A')
	{
		return 14;
	}
}

int translateCardValuePart2(char c)
{
	if (isdigit(c))
	{
		return c - '0';
	}
	else if (c == 'T')
	{
		return 10;
	}
	else if (c == 'J')
	{
		return 0;
	}
	else if (c == 'Q')
	{
		return 12;
	}
	else if (c == 'K')
	{
		return 13;
	}
	else if (c == 'A')
	{
		return 14;
	}
}

class Card
{
public:
	Card(const std::string& _cards, int _winnings, int _cardStrength) : cards(_cards), winnings(_winnings), cardStrength(_cardStrength)
	{
	}

	friend bool operator<(const Card& l, const Card& r)
	{
		if (l.cardStrength != r.cardStrength)
		{
			return l.cardStrength < r.cardStrength;
		}
		
		for (int i = 0; i < l.cards.size(); i++)
		{
			int lValue = translateCardValuePart2(l.cards[i]);
			int rValue = translateCardValuePart2(r.cards[i]);

			if (lValue != rValue)
			{
				return lValue < rValue;
			}
		}
	}

	int getWinnings() const
	{
		return winnings;
	}

private:
	std::string cards;
	int winnings;
	int cardStrength;
};

std::string DaySeven::runChallange()
{
	std::string line;

	int result = 0;

	std::vector<std::unique_ptr<Card>> cardsVector;

	while (std::getline(inputManager->file, line))
	{
		std::unordered_map<int, int> cardMemory;
		std::stringstream ss;
		std::string cardString;
		ss << line;
		ss >> cardString;

		for (char card : cardString)
		{
			int cardValue = translateCardValue(card);

			cardMemory[cardValue]++;
		}

		auto cardStrength = CardStrength::High_Card;

		for (auto cards : cardMemory)
		{
			if (cards.second == 5)
			{
				cardStrength = CardStrength::Five_of_Kind;
			}
			else if (cards.second == 4)
			{
				cardStrength = CardStrength::Four_of_Kind;
			}
			if ((cards.second == 2 && static_cast<int>(cardStrength) == 4) || cards.second == 3 && static_cast<int>(cardStrength) == 2)
			{
				cardStrength = CardStrength::Full_House;
			}
			else if (cards.second == 3)
			{
				cardStrength = CardStrength::Three_of_Kind;
			}
			else if (cards.second == 2 && cardStrength == CardStrength::One_Pair)
			{
				cardStrength = CardStrength::Two_Pair;
			}
			else if (cards.second == 2)
			{
				cardStrength = CardStrength::One_Pair;
			}
		}

		int winnings;

		ss >> winnings;

		cardsVector.push_back(std::unique_ptr<Card>(new Card(cardString, winnings, static_cast<int>(cardStrength))));
	}

	std::sort(cardsVector.begin(), cardsVector.end(), [](const auto& c1, const auto& c2)
		{
			return *c1 < *c2;
		});

	for (int i = 0; i < cardsVector.size(); i++)
	{
		result += cardsVector.at(i)->getWinnings() * (i + 1);
	}

	return std::to_string(result);
}

std::string DaySeven::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	int result = 0;

	std::vector<std::unique_ptr<Card>> cardsVector;

	while (std::getline(inputManager->file, line))
	{
		std::unordered_map<int, int> cardMemory;
		std::stringstream ss;
		std::string cardString;
		ss << line;
		ss >> cardString;

		int jokerAmount = 0;

		for (char card : cardString)
		{
			int cardValue = translateCardValue(card);

			if (card == 'J')
			{
				jokerAmount++;
			}

			cardMemory[cardValue]++;
		}

		auto highestIndex = std::pair<int, int>(-1, -1);

		for (auto cards : cardMemory)
		{
			if (cards.second > highestIndex.second && cards.first != 11)
			{
				highestIndex = cards;
			}
		}

		// Add jokers to highest
		cardMemory[highestIndex.first] += jokerAmount;

		auto cardStrength = CardStrength::High_Card;

		for (auto cards : cardMemory)
		{
			int amountofCards = cards.second;

			if (cards.first == 11)
				continue;

			if (amountofCards == 5)
			{
				cardStrength = CardStrength::Five_of_Kind;
			}
			else if (amountofCards == 4)
			{
				cardStrength = CardStrength::Four_of_Kind;
			}
			if ((amountofCards == 2 && static_cast<int>(cardStrength) == 4) || amountofCards == 3 && static_cast<int>(cardStrength) == 2)
			{
				cardStrength = CardStrength::Full_House;
			}
			else if (amountofCards == 3)
			{
				cardStrength = CardStrength::Three_of_Kind;
			}
			else if (amountofCards == 2 && cardStrength == CardStrength::One_Pair)
			{
				cardStrength = CardStrength::Two_Pair;
			}
			else if (amountofCards == 2)
			{
				cardStrength = CardStrength::One_Pair;
			}
		}

		int winnings;

		ss >> winnings;

		cardsVector.push_back(std::unique_ptr<Card>(new Card(cardString, winnings, static_cast<int>(cardStrength))));
	}

	std::sort(cardsVector.begin(), cardsVector.end(), [](const auto& c1, const auto& c2)
		{
			return *c1 < *c2;
		});

	for (int i = 0; i < cardsVector.size(); i++)
	{
		result += cardsVector.at(i)->getWinnings() * (i + 1);
	}

	return std::to_string(result);
}