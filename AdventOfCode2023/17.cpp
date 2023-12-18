#include "17.h"

#include <iostream>
#include<unordered_set>
#include<unordered_map>
#include"Helpers/PairHash.h"
#include<queue>
#include <iomanip>
#include<unordered_set>
#include<map>
#include<set>
DaySeventeen::DaySeventeen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

namespace {
	enum class Direction
	{
		RIGHT = 0,
		DOWN = 1,
		LEFT = 2,
		UP = 3
	};

	struct Pattern
	{
		Pattern(int _lineCounter, const std::pair<int, int>& _pos, Direction _dir, int _accumulatedHeat) : lineCounter(_lineCounter), pos(_pos), dir(_dir), accumulatedHeat(_accumulatedHeat) {}
		int lineCounter;
		std::pair<int, int> pos;
		Direction dir;
		int accumulatedHeat;
	};

	bool operator<(const Pattern& a, const Pattern& b) { return a.accumulatedHeat > b.accumulatedHeat; }

	int charNumberToInt(char c)
	{
		return c - '0';
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
		std::vector<std::pair<int, int>> dirMove = { {0,1}, {1,0}, {0,-1}, {-1,0} };

		int intDir = static_cast<int>(dir);

		std::pair<int, int> newPos = std::pair<int,int>(pos.first + dirMove[intDir].first, pos.second + dirMove[intDir].second);

		if (isInBounds(matrix, newPos))
		{
			pos = newPos;
			return true;
		}
		else
		{
			return false;
		}
	}

	void pathHelper(const Matrix& matrix, Direction dir, std::priority_queue<Pattern>& queue, const Pattern& pattern, int minLineCounter, int maxLineCounter, std::unordered_set<std::string>& memory)
	{
		auto tmpPos = pattern.pos;
		bool moved = tryMove(matrix, tmpPos, dir);

		if (moved)
		{
			auto newLineCounter = dir == pattern.dir ? pattern.lineCounter + 1 : pattern.lineCounter;
			auto newHeatValue = pattern.accumulatedHeat + charNumberToInt(matrix[tmpPos.first][tmpPos.second]);

			bool straighLineGoal = pattern.dir != dir ? newLineCounter >= minLineCounter : true;

			newLineCounter = dir == pattern.dir ? newLineCounter : 1;

			std::string id = std::to_string(tmpPos.first) + "-" + std::to_string(tmpPos.second) + "-" + std::to_string(static_cast<int>(dir)) + "-" + std::to_string(newLineCounter);

			if (newLineCounter != maxLineCounter && !memory.contains(id) && straighLineGoal)
			{
				memory.insert(id);

				auto newPattern = Pattern(newLineCounter, tmpPos, dir, newHeatValue);
				queue.push(newPattern);
			}
		}
	}



	int path(const Matrix& matrix, int minLineCounter, int maxLineCounter)
	{
		auto startPos = std::pair<int, int>(0, 0);

		std::priority_queue<Pattern> queue;

		queue.push(Pattern(0, startPos, Direction::RIGHT, 0));
		queue.push(Pattern(0, startPos, Direction::DOWN, 0));

		int result = 9999999;

		std::unordered_set<std::string> memory;

		while (!queue.empty())
		{
			Pattern pattern = queue.top();
			queue.pop();

			auto tmpPos = pattern.pos;
			if (tmpPos.first == matrix.size() - 1 && tmpPos.second == matrix.front().size() - 1 && pattern.lineCounter >= minLineCounter)
			{
				result = pattern.accumulatedHeat;
				break;
			}

			auto currentDir = pattern.dir;

			for (int i = -1; i <= 1; i++)
			{
				auto newDir = static_cast<Direction>((static_cast<int>(currentDir) + i) & 0x3);
				pathHelper(matrix, newDir, queue, pattern, minLineCounter, maxLineCounter + 1, memory);
			}
		}

		return result;
	}
}
std::string DaySeventeen::runChallange()
{
	auto matrix = inputManager->getMatrix();

	int res = path(matrix, 1, 3);
	
	return std::to_string(res);
}

std::string DaySeventeen::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	int res = path(matrix, 4, 10);

	return std::to_string(res);
}