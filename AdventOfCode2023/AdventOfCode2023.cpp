// AdventOfCode2023.cpp : Defines the entry point for the application.
//

#include "AdventOfCode2023.h"

#include<iostream>

#include "Helpers/GetInput.h"

#include "1.h"
#include "2.h"
#include "3.h"

using namespace std;

std::unique_ptr<ICodeChallange> GetChallangeFunction(const std::string& day)
{
	auto inputManager = std::make_shared<InputManager>(day);

	if (day == "1")
	{
		return std::make_unique<DayOne>(inputManager);
	}
	else if (day == "2")
	{
		return std::make_unique<DayTwo>(inputManager);
	}
	else if (day == "3")
	{
		return std::make_unique<DayThree>(inputManager);
	}

	return nullptr;
}

int main()
{
	std::string day;

	// Get Current Date

	day = "3";

	auto currentDayChallange = GetChallangeFunction(day);

	//auto answer = currentDayChallange->runChallange();

	//std::cout << "Answer: " << answer << std::endl;

	auto answer2 = currentDayChallange->runChallangePart2();

	std::cout << "Answer 2: " << answer2 << std::endl;

	return 0;
}
