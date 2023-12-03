#include "3.h"

#include "Helpers/GetInput.h"
#include<sstream>
#include<unordered_map>
#include<unordered_set>

#include<iostream>
#include<string.h>
#include<numeric>

DayThree::DayThree(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

bool foundAdjacentSymbol(const Matrix& matrix, int x, int y)
{
	int xStart = std::max(x - 1, 0);
	int yStart = std::max(y - 1, 0);

	int xEnd = std::min(x + 1, (int)matrix.front().size() - 1);
	int yEnd = std::min(y + 1, (int)matrix.size() - 1);

	bool symbolFound = false;

	for (int i = xStart; i <= xEnd; i++)
	{
		for (int j = yStart; j <= yEnd; j++)
		{
			if (!isdigit(matrix[j][i]) && matrix[j][i] != '.')
			{
				symbolFound = true;
			}
		}
	}

	return symbolFound;

}

int testForSymbol(const Matrix& matrix, int& x, int y)
{
	std::string returnResult{};

	bool foundSymbol = false;

	while (isdigit(matrix[y][x]))
	{
		returnResult.push_back(matrix[y][x]);

		foundSymbol |= foundAdjacentSymbol(matrix, x, y);

		x++;

		if (x == matrix.front().size())
			break;
	}

	if (foundSymbol)
	{
		std::cout << returnResult << std::endl;
	}

	return foundSymbol ? std::stoi(returnResult) : 0;
}

std::string DayThree::runChallange()
{
	auto matrix = inputManager->getMatrix();

	int result = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.front().size(); j++)
		{
			if (isdigit(matrix[i][j])) // Number found
			{
				result += testForSymbol(matrix, j, i);
			}
		}
	}

	return std::to_string(result);

}

struct pair_hash {
	inline std::size_t operator()(const std::pair<int, int>& v) const {
		return v.first * 31 + v.second;
	}
};

int findGears(const Matrix& matrix, int x, int y)
{
	int xStart = std::max(x - 1, 0);
	int yStart = std::max(y - 1, 0);

	int xEnd = std::min(x + 1, (int)matrix.front().size() - 1);
	int yEnd = std::min(y + 1, (int)matrix.size() - 1);

	std::unordered_set<std::pair<int, int>, pair_hash> found{};

	std::vector<int> result{};

	for (int i = xStart; i <= xEnd; i++)
	{
		for (int j = yStart; j <= yEnd; j++)
		{
			if (isdigit(matrix[j][i]) && found.count(std::pair<int,int>(j,i)) == 0)
			{
				int findStart = i;
				std::string resultNumber{ matrix[j][i] };

				findStart--;

				// Find left
				while (findStart >= 0 && isdigit(matrix[j][findStart]) )
				{
					resultNumber.insert(0, 1, matrix[j][findStart]);
					found.insert(std::pair<int, int>(j, findStart));
					findStart--;
				}

				findStart = i;

				findStart++;

				// Find right
				while (findStart < (int)matrix.front().size() && isdigit(matrix[j][findStart]))
				{
					resultNumber.push_back(matrix[j][findStart]);
					found.insert(std::pair<int, int>(j, findStart));
					findStart++;
				}

				result.push_back(std::stoi(resultNumber));
			}
		}
	}

	return result.size() == 2 ? std::accumulate(result.begin(), result.end(), 1, std::multiplies<int>()) : 0;
}

std::string DayThree::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	int res = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.front().size(); j++)
		{
			if (matrix[i][j] == '*') // Number found
			{
				res += findGears(matrix, j, i);
			}
		}
	}

	return std::to_string(res);
}