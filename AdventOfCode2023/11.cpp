#include "11.h"

#include <iostream>

#include"Helpers/Point.h"

DayEleven::DayEleven(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

void expandMatrix(Matrix& matrix)
{
	std::vector<bool> columnFound(matrix.front().size(), false);

	for (int row = 0; row < matrix.size(); row++)
	{
		bool rowFound = false;
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '#')
			{
				columnFound[column] = true;

				rowFound = true;
			}
		}
		if (!rowFound)
		{
			matrix.insert(matrix.begin() + row, std::vector<char>(matrix.at(row).size(), '.'));
			row++; // Skip insertet empty row
		}
	}

	int addedColumns = 0;

	for (int i = 0; i < columnFound.size(); i++)
	{
		if (!columnFound.at(i))
		{
			for (auto rowIt = matrix.begin(); rowIt != matrix.end(); rowIt++)
			{
				rowIt->insert(rowIt->begin() + i + addedColumns, '.');
			}
			addedColumns++;
		}
	}
}

std::vector<std::unique_ptr<Point>> getGalaxyPositions(const Matrix& matrix)
{
	std::vector<std::unique_ptr<Point>> galaxyPos{};
	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '#')
			{
				galaxyPos.push_back(std::make_unique<Point>(row, column));
			}
		}
	}

	return galaxyPos;
}

std::string DayEleven::runChallange()
{
	auto matrix = inputManager->getMatrix();

	expandMatrix(matrix);

	auto galaxyPositions = getGalaxyPositions(matrix);

	int sum = 0;

	for (int i = 0; i < galaxyPositions.size(); i++)
	{
		for (int j = i + 1; j < galaxyPositions.size(); j++)
		{
			sum += galaxyPositions.at(i)->distance(*galaxyPositions.at(j));
		}
	}

	return std::to_string(sum);
}

class Galaxy
{
public:
	Galaxy(const std::pair<unsigned long long, unsigned long long>& _startPos) : startPos(_startPos), currentPos(_startPos)
	{
	}
	std::pair<unsigned long long, unsigned long long> currentPos;
	std::pair<unsigned long long, unsigned long long> startPos;
};

void increaseRow(std::vector<std::unique_ptr<Galaxy>>& galaxies, unsigned int row, unsigned int factor)
{
	for (auto& galaxy : galaxies)
	{
		if (galaxy->startPos.first > row)
		{
			galaxy->currentPos.first += factor - 1;
		}
	}
}

void increaseColumn(std::vector<std::unique_ptr<Galaxy>>& galaxies, unsigned int column, unsigned int factor)
{
	for (auto& galaxy : galaxies)
	{
		if (galaxy->startPos.second > column)
		{
			galaxy->currentPos.second += factor - 1;
		}
	}
}

constexpr unsigned int FACTOR = 1000000;

std::string DayEleven::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();
	std::vector<std::unique_ptr<Galaxy>> galaxies;

	for (int row = 0; row < matrix.size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '#')
			{
				galaxies.push_back(std::make_unique<Galaxy>(std::pair<int,int>(row, column)));
			}
		}
	}

	std::vector<bool> columnFound(matrix.front().size(), false);

	for (int row = 0; row < matrix.size(); row++)
	{
		bool rowFound = false;
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '#')
			{
				columnFound[column] = true;

				rowFound = true;
			}
		}
		if (!rowFound)
		{
			increaseRow(galaxies, row, FACTOR);
		}
	}

	for (int i = 0; i < columnFound.size(); i++)
	{
		if (!columnFound.at(i))
		{
			increaseColumn(galaxies, i, FACTOR);
		}
	}

	unsigned long long sum = 0;

	for (int i = 0; i < galaxies.size(); i++)
	{
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			unsigned long long y = galaxies[j]->currentPos.first > galaxies[i]->currentPos.first ? galaxies[j]->currentPos.first - galaxies[i]->currentPos.first : galaxies[i]->currentPos.first - galaxies[j]->currentPos.first;
			unsigned long long x = galaxies[j]->currentPos.second > galaxies[i]->currentPos.second ? galaxies[j]->currentPos.second - galaxies[i]->currentPos.second : galaxies[i]->currentPos.second - galaxies[j]->currentPos.second;
			sum += x + y;
		}
	}

	return std::to_string(sum);
}