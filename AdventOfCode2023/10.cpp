#include "10.h"

#include <iostream>
#include<unordered_set>
#include<queue>

#include"Helpers/PairHash.h"

DayTen::DayTen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

enum class Direction : unsigned int
{
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3
};

void move(char Tile, std::pair<int, int>& pos, Direction& dir)
{
	if (Tile == '|')
	{
		if (dir == Direction::Down)
		{
			pos.first += 1;
		}
		else
		{
			pos.first -= 1;
		}
	}
	else if (Tile == '-')
	{
		if (dir == Direction::Right)
		{
			pos.second += 1;
		}
		else
		{
			pos.second -= 1;
		}
	}
	else if (Tile == 'L')
	{
		if (dir == Direction::Down)
		{
			dir = Direction::Right;
			pos.second += 1;
		}
		else
		{
			dir = Direction::Up;
			pos.first -= 1;
		}
	}
	else if (Tile == 'J')
	{
		if (dir == Direction::Down)
		{
			dir = Direction::Left;
			pos.second -= 1;
		}
		else
		{
			dir = Direction::Up;
			pos.first -= 1;
		}
	}
	else if (Tile == '7')
	{
		if (dir == Direction::Up)
		{
			dir = Direction::Left;
			pos.second -= 1;
		}
		else
		{
			dir = Direction::Down;
			pos.first += 1;
		}
	}
	else if (Tile == 'F')
	{
		if (dir == Direction::Up)
		{
			dir = Direction::Right;
			pos.second += 1;
		}
		else
		{
			dir = Direction::Down;
			pos.first += 1;
		}
	}
	else if (Tile != 'S')
	{
		throw;
	}

}

std::string DayTen::runChallange()
{
	std::string line;

	std::pair<int, int> startPos;

	auto matrix = inputManager->getMatrix();

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.front().size(); j++)
		{
			if (matrix[i][j] == 'S')
			{
				startPos = std::pair<int, int>(i, j);
				break;
			}
		}
	}

	std::vector<std::pair<int, int>> directionHelper = { {0,1}, {0,-1}, {-1,0}, {1,0} };

	int steps = 1;

	for (int i = 0; i < 4; i++)
	{
		auto newPos = std::pair<int, int>(startPos.first + directionHelper[i].first, startPos.second + directionHelper[i].second);
		auto direction = static_cast<Direction>(i);

		if (matrix[newPos.first][newPos.second] != '.')
		{
			while (newPos.first != startPos.first || newPos.second != startPos.second)
			{
				move(matrix[newPos.first][newPos.second], newPos, direction);
				steps++;
			}
			break;
		}
	}

	double longestPath = std::ceil(static_cast<double>(steps) / 2.0);

	return std::to_string(longestPath);

}

void print(const Matrix& matrix, const std::pair<int,int>& p)
{
	std::cout << "PRINT" << std::endl;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.front().size(); j++)
		{
			if (i == p.first && j == p.second)
			{
				std::cout << "X";
			}
			else
				std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::string DayTen::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	Matrix matrix;

	std::pair<int, int> startPos;

	int rowCount = 0;

	while (std::getline(inputManager->file, line))
	{
		std::vector<char> row;
		int columnCount = 0;
		for (char c : line)
		{
			row.push_back(c);

			if (c == 'S')
			{
				startPos = std::pair<int, int>(rowCount, columnCount);
			}
			columnCount++;
		}

		matrix.push_back(row);
		rowCount++;
	}

	std::vector<std::pair<int, int>> directionHelper = { {0,1}, {0,-1}, {-1,0}, {1,0} };
	std::unordered_set<std::pair<int, int>, pair_hash> pathPos2;

	unsigned int rowSize = matrix.size();
	unsigned int columnSize = matrix.front().size();
	unsigned int tileCount = 0;

	Matrix expMatris(rowSize * 2, std::vector<char>(columnSize * 2));
	std::unordered_set<std::pair<int, int>, pair_hash> tileMap;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.front().size(); column++)
		{
			auto tile = matrix[row][column];
			auto newColumn = column * 2;
			auto newRow = row * 2;
			if (tile == '|')
			{
				expMatris[newRow][newColumn] = '|';
				expMatris[newRow + 1][newColumn] = '|';
				expMatris[newRow][newColumn + 1] = '.';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == '-')
			{
				expMatris[newRow][newColumn] = '-';
				expMatris[newRow + 1][newColumn] = '.';
				expMatris[newRow][newColumn + 1] = '-';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == 'L')
			{
				expMatris[newRow][newColumn] = 'L';
				expMatris[newRow + 1][newColumn] = '.';
				expMatris[newRow][newColumn + 1] = '-';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == 'J')
			{
				expMatris[newRow][newColumn] = 'J';
				expMatris[newRow + 1][newColumn] = '.';
				expMatris[newRow][newColumn + 1] = '.';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == '7')
			{
				expMatris[newRow][newColumn] = '7';
				expMatris[newRow + 1][newColumn] = '|';
				expMatris[newRow][newColumn + 1] = '.';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == 'F')
			{
				expMatris[newRow][newColumn] = 'F';
				expMatris[newRow + 1][newColumn] = '|';
				expMatris[newRow][newColumn + 1] = '-';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
			else if (tile == '.')
			{
				expMatris[newRow][newColumn] = '.';
				expMatris[newRow + 1][newColumn] = '.';
				expMatris[newRow][newColumn + 1] = '.';
				expMatris[newRow + 1][newColumn + 1] = '.';

				tileMap.insert({ newRow + 1, newColumn + 1 });

				tileCount += 4;
			}
			else if (tile == 'S') // May depend on input
			{
				expMatris[newRow][newColumn] = 'S';
				expMatris[newRow + 1][newColumn] = '|';
				expMatris[newRow][newColumn + 1] = '-';
				expMatris[newRow + 1][newColumn + 1] = '.';
			}
		}
	}

	expMatris.insert(expMatris.begin(), std::vector<char>(expMatris.front().size(), ' '));

	for (auto it = expMatris.begin(); it != expMatris.end(); it++)
	{
		it->insert(it->begin(), ' ');
	}

	startPos.first *= 2;
	startPos.first += 1;
	startPos.second *= 2;
	startPos.second += 1;

	std::unordered_set<std::pair<int, int>, pair_hash> pathPos;
	
	for (int i = 0; i < 4; i++)
	{
		auto newPos = std::pair<int, int>(startPos.first + directionHelper[i].first, startPos.second + directionHelper[i].second);
		auto direction = static_cast<Direction>(i);
		pathPos.insert(newPos);

		if (expMatris[newPos.first][newPos.second] != '.')
		{
			while (newPos.first != startPos.first || newPos.second != startPos.second)
			{
				move(expMatris[newPos.first][newPos.second], newPos, direction);
				pathPos.insert(newPos);
			}
			break;
		}
	}

	std::queue<std::pair<int, int>> queue;
	queue.push(std::pair<int, int>(0, 0));
	std::unordered_set<std::pair<int, int>, pair_hash> discovered;
	discovered.insert(queue.front());

	unsigned int outsideTile = 0;
	std::unordered_set<std::pair<int, int>, pair_hash> discoveredTiles;

	while (!queue.empty())
	{
		auto element = queue.front();
		queue.pop();

		for (int i = 0; i < 4; i++)
		{
			auto newPos = std::pair<int, int>(element.first + directionHelper[i].first, element.second + directionHelper[i].second);

			if (newPos.first < expMatris.size() && newPos.second < expMatris.front().size() && newPos.first >= 0 && newPos.second >= 0 && !discovered.contains(newPos) && !pathPos.contains(newPos))
			{
				discovered.insert(newPos);
				queue.push(newPos);
				if (expMatris[newPos.first][newPos.second] != ' ')
				{
					outsideTile++;
					discoveredTiles.insert(newPos);
				}
			}
		}
	}
	std::unordered_set<std::pair<int, int>, pair_hash> resultMap;

	for (auto t : tileMap)
	{
		if (!discoveredTiles.contains(t))
			resultMap.insert(t);
	}

	std::unordered_set<std::pair<int, int>, pair_hash> resultMap2;

	unsigned int insideTile = 0;
	std::unordered_set<std::pair<int, int>, pair_hash> discovered2;

	for (auto t : resultMap)
	{
		std::queue<std::pair<int, int>> queue2;
		queue2.push(std::pair<int, int>(t));
		if (!discovered2.contains(queue2.front()))
			resultMap2.insert(queue2.front());
		
		discovered2.insert(queue2.front());

		while (!queue2.empty())
		{
			auto element = queue2.front();
			queue2.pop();

			for (int i = 0; i < 4; i++)
			{
				auto newPos = std::pair<int, int>(element.first + directionHelper[i].first, element.second + directionHelper[i].second);

				if (newPos.first < expMatris.size() && newPos.second < expMatris.front().size() && newPos.first >= 0 && newPos.second >= 0 && !discovered2.contains(newPos) && !pathPos.contains(newPos))
				{
					discovered2.insert(newPos);
					queue2.push(newPos);
					if (expMatris[newPos.first][newPos.second] != ' ')
					{
						resultMap2.insert(newPos);
					}
				}
			}
		}
	}

	int result = 0;
	for (auto t : resultMap2)
	{
		if (t.first % 2 == 1 && t.second % 2 == 1)
		{
			result++;
		}
	}

	return std::to_string(result);
}