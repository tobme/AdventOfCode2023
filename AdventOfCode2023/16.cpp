#include "16.h"

#include <iostream>

#include<unordered_set>
#include"Helpers/PairHash.h"

DaySixteen::DaySixteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

namespace {
	enum class Direction
	{
		RIGHT = 0,
		DOWN = 1,
		LEFT = 2,
		UP = 3,
	};
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
	std::pair<int, int> newPos;
	switch (dir)
	{
	case Direction::RIGHT:
		newPos = std::pair<int, int>(pos.first, pos.second + 1);
		break;
	case Direction::LEFT:
		newPos = std::pair<int, int>(pos.first, pos.second - 1);
		break;
	case Direction::UP:
		newPos = std::pair<int, int>(pos.first - 1, pos.second);
		break;
	case Direction::DOWN:
		newPos = std::pair<int, int>(pos.first + 1, pos.second);
		break;
	}

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

std::unordered_set<std::pair<int, int>, pair_hash> energizedTiles;



void energise(const Matrix& matrix, std::pair<int, int> pos, Direction dir)
{
	if (!isInBounds(matrix, pos))
		return;

	do
	{
		char newTile = matrix[pos.first][pos.second];

		switch (newTile)
		{
			case '\\':
				switch (dir)
				{
				case Direction::RIGHT:
					dir = Direction::DOWN;
					break;
				case Direction::LEFT:
					dir = Direction::UP;
					break;
				case Direction::UP:
					dir = Direction::LEFT;
					break;
				case Direction::DOWN:
					dir = Direction::RIGHT;
					break;
				}
				break;
			case '/':
			{
				switch (dir)
				{
				case Direction::RIGHT:
					dir = Direction::UP;
					break;
				case Direction::LEFT:
					dir = Direction::DOWN;
					break;
				case Direction::UP:
					dir = Direction::RIGHT;
					break;
				case Direction::DOWN:
					dir = Direction::LEFT;
					break;
				}
				break;
			}
			case '|':
				if (energizedTiles.contains(pos))
					return;
				switch (dir)
				{
				case Direction::LEFT:
				case Direction::RIGHT:
					energizedTiles.insert(pos);
					dir = Direction::UP;
					energise(matrix, std::pair<int, int>(pos.first + 1, pos.second), Direction::DOWN);
					break;
				default:
					break;
				}
				break;

			case '-':
				if (energizedTiles.contains(pos))
					return;
				switch (dir)
				{
				case Direction::UP:
				case Direction::DOWN:
					energizedTiles.insert(pos);
					dir = Direction::LEFT;
					energise(matrix, std::pair<int, int>(pos.first, pos.second + 1), Direction::RIGHT);
					break;
				default:
					break;
				}
				break;
			default:
				break;
		}

		energizedTiles.insert(pos);
	} while (tryMove(matrix, pos, dir));
}

int getRes(const Matrix& matrix, std::pair<int, int> pos, Direction dir)
{
	energise(matrix, pos, dir);
	int res = energizedTiles.size();
	energizedTiles = std::unordered_set<std::pair<int, int>, pair_hash>();
	return res;
}

std::string DaySixteen::runChallange()
{
	auto matrix = inputManager->getMatrix();

	int res = getRes(matrix, { 0, 0 }, Direction::RIGHT);

	return std::to_string(res);
}

std::string DaySixteen::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		if (row == 0 || row == matrix.size() - 1)
		{
			for (int column = 0; column < matrix.at(row).size(); column++)
			{
				if (column == 0)
				{
					res = std::max(getRes(matrix, std::pair<int, int>(row, column), Direction::RIGHT), res);
				}
				else if (column == matrix.at(row).size() - 1)
				{
					res = std::max(getRes(matrix, std::pair<int, int>(row, column), Direction::LEFT), res);
				}

				if (row == 0)
				{
					res = std::max(getRes(matrix, std::pair<int, int>(row, column), Direction::DOWN), res);
				}
				else
				{
					res = std::max(getRes(matrix, std::pair<int, int>(row, column), Direction::UP), res);
				}
			}
		}
		else
		{
			res = std::max(getRes(matrix, std::pair<int, int>(row, 0), Direction::RIGHT), res);
			res = std::max(getRes(matrix, std::pair<int, int>(row, matrix.at(row).size() - 1), Direction::LEFT), res);
		}
	}

	return std::to_string(res);
}