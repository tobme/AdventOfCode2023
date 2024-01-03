#include "21.h"

#include <iostream>
#include<queue>
#include<unordered_set>
#include"Helpers/PairHash.h"
#include<unordered_map>

DayTwentyone::DayTwentyone(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

namespace {
	enum class Direction
	{
		RIGHT = 0,
		DOWN = 1,
		LEFT = 2,
		UP = 3,
	};

	std::pair<int, int> findStartPos(const Matrix& matrix)
	{
		for (int row = 0; row < matrix.size(); row++)
		{
			for (int column = 0; column < matrix.at(row).size(); column++)
			{
				if (matrix[row][column] == 'S')
				{
					return { row, column };
				}
			}
		}
		return { 0,0 };
	}

	bool isInBounds(const Matrix& matrix, const std::pair<int, int>& pos)
	{
		return pos.first >= 0 &&
			pos.second >= 0 &&
			pos.first < matrix.size() &&
			pos.second < matrix.front().size();
	}

	bool tryMove(const Matrix& matrix, std::pair<int, int>& pos, Direction dir)
	{
		std::vector<std::pair<int, int>> dirMove = { {0,1}, {1,0}, {0,-1}, {-1,0}};

		auto maxRow = matrix.size();
		auto maxColumn = matrix.front().size();

		int intDir = static_cast<int>(dir);

		std::pair<int, int> newPos = pos;

		newPos = std::pair<int, int>(pos.first + dirMove[intDir].first, pos.second + dirMove[intDir].second);

		// Find relative pos

		if (matrix[newPos.first][newPos.second] == '#')
			return false;

		pos = newPos;
		return true;
	}

	struct Data
	{
		std::pair<int, int> pos;
		unsigned int steps;
	};
}

int getLavasVisited(const Matrix& matrix, const std::pair<int,int>& startPos, int maxSteps)
{

	std::queue<Data> queue;
	queue.push(Data(startPos, 0));

	std::unordered_set<std::pair<int, int>, pair_hash> visited;

	int res = 0;

	while (!queue.empty())
	{
		auto d = queue.front();
		queue.pop();

		if (d.steps % 2 == 0)
		{
			res++;
		}

		for (int i = 0; i < 4; i++)
		{
			auto tmpPos = d.pos;

			bool success = tryMove(matrix, tmpPos, static_cast<Direction>(i));

			if (success && !visited.contains(tmpPos))
			{
				int newSteps = d.steps + 1;
				if (newSteps <= maxSteps)
				{
					queue.push(Data(tmpPos, newSteps));
					visited.insert(tmpPos);
				}
			}
		}
	}

	return res;
}

std::string DayTwentyone::runChallange()
{
	auto matrix = inputManager->getMatrix();

	std::pair<int, int> startPos = findStartPos(matrix);

	int res = getLavasVisited(matrix, startPos, 64);

	return std::to_string(res);
}

std::string DayTwentyone::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	int evenResPerMap = getLavasVisited(matrix, { 0,0 }, 99999);
	int unEvenPerMap = getLavasVisited(matrix, {0, 1}, 99999);

	int width = matrix.front().size();
	int height = matrix.front().size();

	int totalSteps = 26501365;

	int maps = totalSteps / width;

	int stepsLeft = (maps * width) + (width / 2);

	bool startUneven = maps % 2 == 0;

	long long res = 0;

	std::pair<int, int> startPos = startUneven ? std::pair<int,int>{height - 2, width / 2} : std::pair<int, int>{height - 1, width / 2};

	// Up
	res += getLavasVisited(matrix, startPos, startUneven ? stepsLeft - 1 : stepsLeft);

	// Down
	startPos = startUneven ? std::pair<int, int>{1, width / 2} : std::pair<int, int>{ 0, width / 2 };
	res += getLavasVisited(matrix, startPos, startUneven ? stepsLeft - 1 : stepsLeft);

	// Left
	startPos = startUneven ? std::pair<int, int>{height/2, width - 2} : std::pair<int, int>{ height /2, width - 1 };
	res += getLavasVisited(matrix, startPos, startUneven ? stepsLeft - 1 : stepsLeft);

	// Right
	startPos = startUneven ? std::pair<int, int>{height / 2, 1} : std::pair<int, int>{ height / 2, 0 };
	res += getLavasVisited(matrix, startPos, startUneven ? stepsLeft - 1 : stepsLeft);

	return std::to_string(res);
}