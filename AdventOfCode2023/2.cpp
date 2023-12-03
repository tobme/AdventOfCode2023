#include "2.h"

#include "Helpers/GetInput.h"
#include<sstream>
#include<unordered_map>

#include<string.h>

DayTwo::DayTwo(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayTwo::runChallange()
{
    std::unordered_map<std::string, int> maxValues{ {"red", 12 }, {"green", 13}, {"blue", 14} };

    std::string line;
    
    std::stringstream ss;

    std::string skip;
    int id;
    int quantity;
    std::string color;

    int result = 0;

    while (std::getline(inputManager->file, line))
    {
        ss = std::stringstream();

        ss << line;
        ss >> skip;
        ss >> id;
        ss >> skip;

        bool gameOver = false;
        bool last = false;

        std::unordered_map<std::string, int> currentValues;

        while (!ss.eof())
        {
            ss >> quantity;
            ss >> color;

            if (color.find(';') != std::string::npos)
            {
                gameOver = true;
                color.pop_back();
            }
            else if (color.find(',') != std::string::npos)
            {
                color.pop_back();
            }
            else
            {
                gameOver = true;
                last = true;
            }

            currentValues[color] += quantity;

            if (gameOver)
            {
                if (currentValues["red"] > maxValues["red"] || currentValues["green"] > maxValues["green"] || currentValues["blue"] > maxValues["blue"])
                {
                    break;
                }
                gameOver = false;
                currentValues.clear();

                if (last)
                {
                    result += id;
                    last = false;
                }
            }
        }
    }
    

	return std::to_string(result);
}

std::string DayTwo::runChallangePart2()
{

    std::unordered_map<std::string, int> maxValues{ {"red", 12 }, {"green", 13}, {"blue", 14} };


    std::string line;

    std::stringstream ss;

    std::string skip;
    int id;
    int quantity;
    std::string color;

    int result = 0;

    while (std::getline(inputManager->file, line))
    {
        ss = std::stringstream();

        ss << line;
        ss >> skip;
        ss >> id;
        ss >> skip;

        bool last = false;

        std::unordered_map<std::string, int> smallestValue;

        while (!ss.eof())
        {
            ss >> quantity;
            ss >> color;

            if (color.find(';') != std::string::npos)
            {
                color.pop_back();
            }
            else if (color.find(',') != std::string::npos)
            {
                color.pop_back();
            }
            else
            {
                last = true;
            }

            if (quantity > smallestValue[color])
            {
                smallestValue[color] = quantity;
            }

            if (last)
            {
                result += smallestValue["red"] * smallestValue["green"] * smallestValue["blue"];
            }
        }
    }
    return std::to_string(result);
}