#include "23.h"

#include <iostream>
#include<queue>
#include<unordered_map>
#include "Helpers/Utilities.h"
#include<unordered_set>
#include "Helpers/PairHash.h"

using namespace Util;

namespace {
	enum class Direction
	{
		RIGHT,
		DOWN,
		LEFT,
		UP
	};

	struct Data
	{
		std::pair<int, int> currentPos;
		std::pair<int, int> startPos;
		unsigned int steps;
		std::unordered_set<std::pair<int, int>, pair_hash> visited;
	};
}


DayTwentythree::DayTwentythree(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayTwentythree::runChallange()
{
	return "0";
	auto matrix = inputManager->getMatrix();

	std::pair<int, int> startPos;

	for (int i = 0; i < matrix.front().size(); i++)
	{
		if (matrix.front().at(i) == '.')
		{
			startPos = { 0, i };
		}
	}

	std::pair<int, int> endPos;

	for (int i = 0; i < matrix.back().size(); i++)
	{
		if (matrix.back().at(i) == '.')
		{
			endPos = { matrix.size()-1, i };
		}
	}

	std::unordered_map<char, std::pair<int, int>> arrowHelp = { {'<', {0,-1}}, {'>', {0,1}}, {'^', {-1,0}}, {'v', {1,0}} };
	std::unordered_map<Direction, std::pair<int, int>> dirHelp = { {Direction::LEFT, {0,-1}}, {Direction::RIGHT, {0,1}}, {Direction::UP, {-1,0}}, {Direction::DOWN, {1,0}} };

	auto cmp = [](const Data& lhs, const Data& rhs)
	{
		return lhs.steps < rhs.steps;
	};

	std::priority_queue<Data, std::vector<Data>, decltype(cmp)> queue(cmp);

	queue.push(Data(startPos,startPos,0));

	std::vector<int> res;

	while (!queue.empty())
	{
		auto e = queue.top();
		auto pos = e.startPos;
		e.visited.insert(pos);
		queue.pop();

		if (pos.first == endPos.first && pos.second == endPos.second)
		{
			std::cout << "Answer: " << e.steps << std::endl;
			res.push_back(e.steps);
			continue;
		}

		if (matrix[pos.first][pos.second] == '<' ||
			matrix[pos.first][pos.second] == '>' ||
			matrix[pos.first][pos.second] == '^' ||
			matrix[pos.first][pos.second] == 'v')
		{
			std::pair<int,int> newPos = { pos.first + arrowHelp[matrix[pos.first][pos.second]].first, pos.second + arrowHelp[matrix[pos.first][pos.second]].second };

			if (isInBounds(newPos, matrix) && !e.visited.contains(newPos) && matrix[newPos.first][newPos.second] != '#')
			{
				queue.push(Data(newPos, newPos, e.steps + 1, e.visited));
			}
		}
		else
		{
			std::pair<int,int> newPosR = { pos.first + dirHelp[Direction::RIGHT].first, pos.second + dirHelp[Direction::RIGHT].second };

			if (isInBounds(newPosR, matrix) && !e.visited.contains(newPosR) && matrix[newPosR.first][newPosR.second] != '#')
			{
				queue.push(Data(newPosR, newPosR, e.steps + 1, e.visited));
			}

			std::pair<int, int> newPosD = { pos.first + dirHelp[Direction::DOWN].first, pos.second + dirHelp[Direction::DOWN].second };

			if (isInBounds(newPosD, matrix) && !e.visited.contains(newPosD) && matrix[newPosD.first][newPosD.second] != '#')
			{
				queue.push(Data(newPosD, newPosR, e.steps + 1, e.visited));
			}

			std::pair<int, int> newPosL = { pos.first + dirHelp[Direction::LEFT].first, pos.second + dirHelp[Direction::LEFT].second };

			if (isInBounds(newPosL, matrix) && !e.visited.contains(newPosL) && matrix[newPosL.first][newPosL.second] != '#')
			{
				queue.push(Data(newPosL, newPosR, e.steps + 1, e.visited));
			}

			std::pair<int, int> newPosU = { pos.first + dirHelp[Direction::UP].first, pos.second + dirHelp[Direction::UP].second };

			if (isInBounds(newPosU, matrix) && !e.visited.contains(newPosU) && matrix[newPosU.first][newPosU.second] != '#')
			{
				queue.push(Data(newPosU, newPosR, e.steps + 1, e.visited));
			}
		}
	}

	std::sort(res.begin(), res.end(), std::less<int>());

	return std::to_string(res.back());
}

namespace {
	struct Nodes
	{
		int steps;
		std::pair<int, int> pos;
	};

	int getLongestWalk(const std::pair<int,int>& currentPos,
		const std::pair<int, int>& endPos,
		const std::unordered_map<std::pair<int, int>, std::vector<Nodes>, pair_hash >& gateways,
		std::unordered_set<std::pair<int, int>, pair_hash> visited,
		int steps)
	{
		if (currentPos == endPos)
		{
			std::cout << "Ret steps: " << steps << std::endl;
			return steps;
		}

		int res = 0;

		visited.insert(currentPos);

		auto v = gateways.at(currentPos);

		for (const auto& a : v)
		{
			if (!visited.contains(a.pos))
			{
				res = std::max(res, getLongestWalk(a.pos, endPos, gateways, visited, steps + a.steps));
			}
		}

		return res;
	}
}

std::string DayTwentythree::runChallangePart2()
{
	auto matrix = inputManager->getMatrix();

	std::cout << "start 2: " << std::endl;

	std::pair<int, int> startPos;

	for (int i = 0; i < matrix.front().size(); i++)
	{
		if (matrix.front().at(i) == '.')
		{
			startPos = { 0, i };
		}
	}

	std::pair<int, int> endPos;

	for (int i = 0; i < matrix.back().size(); i++)
	{
		if (matrix.back().at(i) == '.')
		{
			endPos = { matrix.size() - 1, i };
		}
	}

	std::unordered_map<Direction, std::pair<int, int>> dirHelp = { {Direction::LEFT, {0,-1}}, {Direction::RIGHT, {0,1}}, {Direction::UP, {-1,0}}, {Direction::DOWN, {1,0}} };

	auto cHelp = [&matrix](const std::pair<int, int>& p)
	{
		if (!isInBounds(p, matrix))
			return 1;

		if (matrix[p.first][p.second] == '#')
			return 1;

		return 0;
	};

	std::unordered_map<std::pair<int, int>, std::vector<Nodes>, pair_hash> gateways;

	for (int row = 0; row < matrix.front().size(); row++)
	{
		for (int column = 0; column < matrix.at(row).size(); column++)
		{
			if (matrix[row][column] == '#')
				continue;

			std::pair<int,int> rPos = { row + dirHelp[Direction::RIGHT].first, column + dirHelp[Direction::RIGHT].second };
			std::pair<int, int> lPos = { row + dirHelp[Direction::LEFT].first, column + dirHelp[Direction::LEFT].second };
			std::pair<int, int> dPos = { row + dirHelp[Direction::DOWN].first, column + dirHelp[Direction::DOWN].second };
			std::pair<int, int> uPos = { row + dirHelp[Direction::UP].first, column + dirHelp[Direction::UP].second };

			int r = cHelp(rPos);
			r += cHelp(lPos);
			r += cHelp(dPos);
			r += cHelp(uPos);

			if (isInBounds({ row,column }, matrix) && r <= 1)
			{
				gateways[{row,column}] = std::vector<Nodes>();
			}
		}
	}



	std::queue<Data> queue;

	for (const auto& p : gateways)
	{
		queue.push(Data(p.first, p.first, 0));
	}

	gateways[startPos] = std::vector<Nodes>();

	queue.push(Data(startPos, startPos, 0));

	while (!queue.empty())
	{
		auto e = queue.front();
		auto pos = e.currentPos;
		e.visited.insert(pos);
		queue.pop();

		if (pos != e.startPos && (gateways.contains(pos) || (pos.first == endPos.first && pos.second == endPos.second)))
		{
			gateways[e.startPos].push_back(Nodes(e.steps, pos));
			continue;
		}

		std::pair<int, int> newPosR = { pos.first + dirHelp[Direction::RIGHT].first, pos.second + dirHelp[Direction::RIGHT].second };

		if (isInBounds(newPosR, matrix) && !e.visited.contains(newPosR) && matrix[newPosR.first][newPosR.second] != '#')
		{
			queue.push(Data(newPosR, e.startPos, e.steps + 1, e.visited));
		}

		std::pair<int, int> newPosD = { pos.first + dirHelp[Direction::DOWN].first, pos.second + dirHelp[Direction::DOWN].second };

		if (isInBounds(newPosD, matrix) && !e.visited.contains(newPosD) && matrix[newPosD.first][newPosD.second] != '#')
		{
			queue.push(Data(newPosD, e.startPos, e.steps + 1, e.visited));
		}

		std::pair<int, int> newPosL = { pos.first + dirHelp[Direction::LEFT].first, pos.second + dirHelp[Direction::LEFT].second };

		if (isInBounds(newPosL, matrix) && !e.visited.contains(newPosL) && matrix[newPosL.first][newPosL.second] != '#')
		{
			queue.push(Data(newPosL, e.startPos, e.steps + 1, e.visited));
		}

		std::pair<int, int> newPosU = { pos.first + dirHelp[Direction::UP].first, pos.second + dirHelp[Direction::UP].second };

		if (isInBounds(newPosU, matrix) && !e.visited.contains(newPosU) && matrix[newPosU.first][newPosU.second] != '#')
		{
			queue.push(Data(newPosU, e.startPos, e.steps + 1, e.visited));
		}
	}

	int res = getLongestWalk(startPos, endPos, gateways, std::unordered_set<std::pair<int,int>,pair_hash>(), 0);


	return std::to_string(res);
}