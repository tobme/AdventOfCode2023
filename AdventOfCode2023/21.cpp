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
		SOUTHWEST = 4,
		SOUTHEAST = 5,
		NORTHEAST = 6,
		NORTHWEST = 7
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

	bool tryMove(const Matrix& matrix, std::pair<int, int>& pos, Direction dir, int mult = 1)
	{
		std::vector<std::pair<int, int>> dirMove = { {0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1,-1}, {-1,-1}, {-1,1}};

		int intDir = static_cast<int>(dir);

		std::pair<int, int> newPos = pos;

		if (dir == Direction::SOUTHWEST ||
			dir == Direction::SOUTHEAST ||
			dir == Direction::NORTHEAST ||
			dir == Direction::NORTHWEST)
		{
			auto newPos2 = pos;

			while (mult > 0)
			{
				newPos.first = newPos.first + dirMove[intDir].first;
				newPos2.second = newPos2.second + dirMove[intDir].second;

				if (!isInBounds(matrix, newPos) || !isInBounds(matrix, newPos2) || (matrix[newPos.first][newPos.second] == '#' && matrix[newPos2.first][newPos2.second] == '#'))
					return false;

				newPos.second = newPos.second + dirMove[intDir].second;
				if (!isInBounds(matrix, newPos) || matrix[newPos.first][newPos.second] == '#')
					return false;
				mult--;
			}
		}
		else
		{

			while (mult > 0)
			{
				newPos.first = newPos.first + dirMove[intDir].first;
				if (!isInBounds(matrix, newPos) || matrix[newPos.first][newPos.second] == '#')
					return false;

				newPos.second = newPos.second + dirMove[intDir].second;
				if (!isInBounds(matrix, newPos) || matrix[newPos.first][newPos.second] == '#')
					return false;
				mult--;
			}
		}

		pos = newPos;
		return true;
	}

	bool tryMovePart2(const Matrix& matrix, std::pair<int, int>& pos, Direction dir)
	{
		std::vector<std::pair<int, int>> dirMove = { {0,1}, {1,0}, {0,-1}, {-1,0}};

		auto maxRow = matrix.size();
		auto maxColumn = matrix.front().size();

		int intDir = static_cast<int>(dir);

		std::pair<int, int> newPos = pos;

		newPos = std::pair<int, int>(pos.first + dirMove[intDir].first, pos.second + dirMove[intDir].second);

		// Find relative pos

		auto relNewpos = newPos;

		while (relNewpos.first < 0)
		{
			relNewpos.first += maxRow;
		}
		while (relNewpos.second < 0)
		{
			relNewpos.second += maxColumn;
		}

		relNewpos = std::pair<int, int>(relNewpos.first % maxRow, relNewpos.second % maxColumn);
		if (matrix[relNewpos.first][relNewpos.second] == '#')
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

std::string DayTwentyone::runChallange()
{
	auto matrix = inputManager->getMatrix();

	std::pair<int, int> startPos = findStartPos(matrix);

	std::queue<Data> queue;
	queue.push(Data(startPos, 0));

	std::unordered_set<std::pair<int, int>, pair_hash> visited;

	while (!queue.empty())
	{
		auto d = queue.front();
		queue.pop();

		for (int i = 0; i < 8; i++)
		{
			auto tmpPos = d.pos;
			int intMult = i < 4 ? 2 : 1;

			bool success = tryMove(matrix, tmpPos, static_cast<Direction>(i), intMult);

			if (success && !visited.contains(tmpPos))
			{
				int newSteps = d.steps + 2;
				if (newSteps <= 64)
				{
					queue.push(Data(tmpPos, newSteps));
					visited.insert(tmpPos);
				}
			}
		}
	}

	int res = visited.size();

	return std::to_string(res);
}

std::string DayTwentyone::runChallangePart2()
{
	return "0";
}