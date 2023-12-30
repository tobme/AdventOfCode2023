// AdventOfCode2023.cpp : Defines the entry point for the application.
//

#include "AdventOfCode2023.h"

#include<iostream>
#include <chrono>

#include "Helpers/GetInput.h"

#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"
#include "5.h"
#include "6.h"
#include "7.h"
#include "8.h"
#include "9.h"
#include "10.h"
#include "11.h"
#include "12.h"
#include "13.h"
#include "14.h"
#include "15.h"
#include "16.h"
#include "17.h"
#include "18.h"
#include "19.h"
#include "20.h"
#include "21.h"
#include "22.h"
#include "23.h"
#include "24.h"
#include "25.h"

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
	else if (day == "4")
	{
		return std::make_unique<DayFour>(inputManager);
	}
	else if (day == "5")
	{
		return std::make_unique<DayFive>(inputManager);
	}
	else if (day == "6")
	{
		return std::make_unique<DaySix>(inputManager);
	}
	else if (day == "7")
	{
		return std::make_unique<DaySeven>(inputManager);
	}
	else if (day == "8")
	{
		return std::make_unique<DayEight>(inputManager);
	}
	else if (day == "9")
	{
		return std::make_unique<DayNine>(inputManager);
	}
	else if (day == "10")
	{
		return std::make_unique<DayTen>(inputManager);
	}
	else if (day == "11")
	{
		return std::make_unique<DayEleven>(inputManager);
	}
	else if (day == "12")
	{
		return std::make_unique<DayTwelve>(inputManager);
	}
	else if (day == "13")
	{
		return std::make_unique<DayThirteen>(inputManager);
	}
	else if (day == "14")
	{
		return std::make_unique<DayFourteen>(inputManager);
	}
	else if (day == "15")
	{
		return std::make_unique<DayFifteen>(inputManager);
	}
	else if (day == "16")
	{
		return std::make_unique<DaySixteen>(inputManager);
	}
	else if (day == "17")
	{
		return std::make_unique<DaySeventeen>(inputManager);
	}
	else if (day == "18")
	{
		return std::make_unique<DayEighteen>(inputManager);
	}
	else if (day == "19")
	{
		return std::make_unique<DayNineteen>(inputManager);
	}
	else if (day == "20")
	{
		return std::make_unique<DayTwenty>(inputManager);
	}
	else if (day == "21")
	{
		return std::make_unique<DayTwentyone>(inputManager);
	}
	else if (day == "22")
	{
		return std::make_unique<DayTwentytwo>(inputManager);
	}
	else if (day == "23")
	{
		return std::make_unique<DayTwentythree>(inputManager);
	}
	else if (day == "24")
	{
		return std::make_unique<DayTwentyfour>(inputManager);
	}
	else if (day == "25")
	{
		return std::make_unique<DayTwentyfive>(inputManager);
	}

	return nullptr;
}

int main()
{
	std::string day;

	// Get Current Date

	day = "22";

	auto currentDayChallange = GetChallangeFunction(day);

	auto beg = std::chrono::high_resolution_clock::now();

	auto answer = currentDayChallange->runChallange();

	auto end = std::chrono::high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::milliseconds>(end - beg);

	std::cout << "Answer: " << answer << " It took: " << duration << std::endl;

	beg = std::chrono::high_resolution_clock::now();

	auto answer2 = currentDayChallange->runChallangePart2();

	end = std::chrono::high_resolution_clock::now();

	duration = duration_cast<std::chrono::milliseconds>(end - beg);

	std::cout << "Answer 2: " << answer2 << " It took: " << duration << std::endl;

	return 0;
}
