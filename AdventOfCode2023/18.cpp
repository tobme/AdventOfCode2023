#include "18.h"

#include <iostream>
#include<sstream>
#include<unordered_set>
#include"Helpers/Point.h"
#include<unordered_map>
#include<queue>
#include"Helpers/PairHash.h"
#include<set>
#include <numeric>

DayEighteen::DayEighteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

std::string DayEighteen::runChallange()
{
	std::string line;

	Point currentPos(0, 0);

	std::unordered_set<Point, PointHashFunction> lavas;

	std::unordered_map<std::string, Point> dirMap = { {"R", Point(0,1)}, {"D", Point(1,0)}, {"L", Point(0,-1)}, {"U", Point(-1,0)} };

	int startRow = 0;
	int endRow = 0;

	int startCol = 0;
	int endCol = 0;

	while (getline(inputManager->file, line))
	{
		std::stringstream ss;
		std::string dir;
		ss << line;
		ss >> dir;
		int number;
		ss >> number;

		for (int i = 0; i < number; i++)
		{
			currentPos = currentPos + dirMap[dir];
			lavas.insert(currentPos);

			// Find grid
			startRow = std::min(startRow, currentPos.x);
			endRow = std::max(endRow, currentPos.x);

			startCol = std::min(startCol, currentPos.y);
			endCol = std::max(endCol, currentPos.y);
		}
	}

	Point fillStartPos{ startRow - 1, startCol - 1 };
	std::queue<Point> queue;
	queue.push(fillStartPos);

	std::unordered_set<Point, PointHashFunction> visited;

	while (!queue.empty())
	{
		auto p = queue.front();
		queue.pop();

		auto r = p + dirMap["R"];
		if (r.x >= startRow - 1 && r.x <= endRow + 1 &&
			r.y >= startCol - 1 && r.y <= endCol + 1 &&
			!visited.contains(r) && !lavas.contains(r))
		{
			queue.push(r);
			visited.insert(r);
		}

		auto l = p + dirMap["L"];
		if (l.x >= startRow - 1 && l.x <= endRow + 1 &&
			l.y >= startCol - 1 && l.y <= endCol + 1 &&
			!visited.contains(l) && !lavas.contains(l))
		{
			queue.push(l);
			visited.insert(l);
		}

		auto u = p + dirMap["U"];
		if (u.x >= startRow - 1 && u.x <= endRow + 1 &&
			u.y >= startCol - 1 && u.y <= endCol + 1 &&
			!visited.contains(u) && !lavas.contains(u))
		{
			queue.push(u);
			visited.insert(u);
		}

		auto d = p + dirMap["D"];
		if (d.x >= startRow - 1 && d.x <= endRow + 1 &&
			d.y >= startCol - 1 && d.y <= endCol + 1 &&
			!visited.contains(d) && !lavas.contains(d))
		{
			queue.push(d);
			visited.insert(d);
		}
	}

	int res = ( (abs( (startRow - 1) - (endRow + 1) ) + 1) * (abs((startCol - 1) - (endCol + 1)) + 1) ) - visited.size();

	return std::to_string(res);
}

int GcdOfArray(std::vector<long long>& arr, int idx)
{
	if (idx == arr.size() - 1) {
		return arr[idx];
	}
	int a = arr[idx];
	int b = GcdOfArray(arr, idx + 1);
	return std::gcd(
		a, b); // __gcd(a,b) is inbuilt library function 
}

std::string DayEighteen::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	std::pair<long long, long long> currentPos(0, 0);

	auto pSort = [](const std::pair<long long, long long>& a1, const std::pair<long long, long long>& a2) -> bool
	{
		if (a1.first != a2.first)
			return a1.first < a2.first;
		else
			return a1.second < a2.second;
	};

	auto pSort2 = [](const std::pair<long long, long long>& a1, const std::pair<long long, long long>& a2) -> bool
	{
		if (a1.second != a2.second)
			return a1.second < a2.second;
		else
			return a1.first < a2.first;
	};

	std::vector<std::pair<long long, long long>> lavas;

	std::vector<std::pair<int,int>> dirMap = { {0,1}, {1,0}, {0,-1}, {-1,0} };

	long long startRow = 0;
	long long endRow = 0;

	long long startCol = 0;
	long long endCol = 0;

	while (getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;
		ss >> line;
		ss >> line;

		std::string hexCode;
		ss >> hexCode;

		hexCode.pop_back();
		hexCode.erase(0, 1);

		char numb = hexCode.back();
		int dir = numb - '0';
		hexCode.pop_back();

		hexCode = hexCode.substr(1);

		ss = std::stringstream{};

		ss << hexCode;

		int hexV;
		ss >> std::hex >> hexV;

		lavas.push_back(currentPos);
		currentPos.first = currentPos.first + (dirMap[dir].first * hexV);
		currentPos.second = currentPos.second + (dirMap[dir].second * hexV);

		// Find grid
		startRow = std::min(startRow, currentPos.first);
		endRow = std::max(endRow, currentPos.first);

		startCol = std::min(startCol, currentPos.second);
		endCol = std::max(endCol, currentPos.second);
	}

	std::sort(lavas.begin(), lavas.end(), pSort);


	/*
	Point fillStartPos{ startRow - 1, startCol - 1 };
	std::queue<Point> queue;
	queue.push(fillStartPos);

	std::unordered_set<Point, PointHashFunction> visited;

	while (!queue.empty())
	{
		auto p = queue.front();
		queue.pop();

		auto r = p + dirMap["R"];
		if (r.x >= startRow - 1 && r.x <= endRow + 1 &&
			r.y >= startCol - 1 && r.y <= endCol + 1 &&
			!visited.contains(r) && !lavas.contains(r))
		{
			queue.push(r);
			visited.insert(r);
		}

		auto l = p + dirMap["L"];
		if (l.x >= startRow - 1 && l.x <= endRow + 1 &&
			l.y >= startCol - 1 && l.y <= endCol + 1 &&
			!visited.contains(l) && !lavas.contains(l))
		{
			queue.push(l);
			visited.insert(l);
		}

		auto u = p + dirMap["U"];
		if (u.x >= startRow - 1 && u.x <= endRow + 1 &&
			u.y >= startCol - 1 && u.y <= endCol + 1 &&
			!visited.contains(u) && !lavas.contains(u))
		{
			queue.push(u);
			visited.insert(u);
		}

		auto d = p + dirMap["D"];
		if (d.x >= startRow - 1 && d.x <= endRow + 1 &&
			d.y >= startCol - 1 && d.y <= endCol + 1 &&
			!visited.contains(d) && !lavas.contains(d))
		{
			queue.push(d);
			visited.insert(d);
		}
	}
	
	int res = ((abs((startRow - 1) - (endRow + 1)) + 1) * (abs((startCol - 1) - (endCol + 1)) + 1)) - visited.size();
	*/

	int res = 0;
	return std::to_string(res);
}