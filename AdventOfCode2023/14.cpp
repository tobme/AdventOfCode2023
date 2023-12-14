#include "14.h"

#include <iostream>
#include<unordered_map>

DayFourteen::DayFourteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

enum class Direction : unsigned int
{
	NORTH = 0,
	WEST = 1,
	SOUTH = 2,
	EAST = 3
};

void print(const Matrix& matrix)
{
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			std::cout << matrix[row][column];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::pair<int,int> fallInDirection(int row, int column, Direction dir)
{
	switch (dir)
	{
	case Direction::NORTH:
		return std::pair<int, int>(row - 1, column);
	case Direction::WEST:
		return std::pair<int, int>(row, column - 1);
	case Direction::SOUTH:
		return std::pair<int, int>(row + 1, column);
	default:
		return std::pair<int, int>(row, column + 1);
	}
}

bool isInBounds(const std::pair<int, int>& pos, const Matrix& matrix)
{
	return pos.first >= 0 &&
		pos.second >= 0 &&
		pos.first < matrix.size() &&
		pos.second < matrix.front().size();
}

void tilt(Matrix& matrix, Direction dir)
{
	if (dir == Direction::NORTH || dir == Direction::WEST)
	{
		for (int row = 0; row < matrix.size(); row++)
		{
			for (int column = 0; column < matrix.at(row).size(); column++)
			{
				if (matrix[row][column] == 'O')
				{
					auto lastPos = std::pair<int, int>(row, column);
					auto newPos = fallInDirection(row, column, dir);
					while (isInBounds(newPos, matrix) && matrix[newPos.first][newPos.second] == '.')
					{
						std::swap(matrix[lastPos.first][lastPos.second], matrix[newPos.first][newPos.second]);
						lastPos = newPos;
						newPos = fallInDirection(lastPos.first, lastPos.second, dir);
					}
				}
			}
		}
	}
	else if (dir == Direction::EAST || dir == Direction::SOUTH) // Go from opposite direction to fall in correct order
	{
		for (int row = matrix.size() - 1; row >= 0; row--)
		{
			for (int column = matrix.at(row).size() - 1; column >= 0; column--)
			{
				if (matrix[row][column] == 'O')
				{
					auto lastPos = std::pair<int, int>(row, column);
					auto newPos = fallInDirection(row, column, dir);
					while (isInBounds(newPos, matrix) && matrix[newPos.first][newPos.second] == '.')
					{
						std::swap(matrix[lastPos.first][lastPos.second], matrix[newPos.first][newPos.second]);
						lastPos = newPos;
						newPos = fallInDirection(lastPos.first, lastPos.second, dir);
					}
				}
			}
		}
	}
}

std::string getMatrixID(const Matrix& matrix)
{
	std::string res = "";

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			res += matrix[row][column];
		}
	}
	return res;
}

namespace {
	std::unordered_map<std::string, int> memory;
}

void tiltCycle(Matrix& matrix)
{
	for (int i = 0; i < 4; i++)
	{
		tilt(matrix, static_cast<Direction>(i));
	}
}

int findCycle(Matrix& matrix, int index)
{
	std::string ID;

	ID = getMatrixID(matrix);

	if (memory.contains(ID))
	{
		return memory[ID];
	}

	tiltCycle(matrix);

	memory.insert({ ID, index });

	return -1;
}

int countLoad(const Matrix& matrix)
{
	int res = 0;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == 'O')
			{
				res += matrix.size() - row;
			}
		}
	}

	return res;
}

std::string DayFourteen::runChallange()
{
	auto matrix = inputManager->getMatrix();

	tilt(matrix, Direction::NORTH);

	int res = countLoad(matrix);

	return std::to_string(res);
}

std::string DayFourteen::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	int repeatedIndex = 0; // Index when the cycle is repeated
	int cycleLength = 0;

	unsigned long long totLength = 1000000000;

	int foundIndex = 0; // Index of the first time the matrix appeared

	for (unsigned long long i = 0; i < totLength; i++)
	{
		if ((foundIndex = findCycle(matrix, i)) != -1) // Cycle is found
		{
			repeatedIndex = i;
			cycleLength = repeatedIndex - foundIndex;
			break;
		}
	}

	int remainingLength = (totLength - foundIndex) % cycleLength;

	for (int i = 0; i < remainingLength; i++)
	{
		tiltCycle(matrix);
	}

	int res = countLoad(matrix);

	return std::to_string(res);
}