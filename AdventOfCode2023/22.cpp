#include "22.h"

#include <iostream>
#include "Helpers/Utilities.h"
#include <algorithm>
#include<unordered_map>
#include<unordered_set>

DayTwentytwo::DayTwentytwo(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

namespace {
	class Block
	{
	public:

		int xStart;
		int yStart;
		int zStart;

		int xEnd;
		int yEnd;
		int zEnd;

		bool interSect(const Block& b)
		{
			return std::max(xStart, b.xStart) <= std::min(xEnd, b.xEnd) &&
				std::max(yStart, b.yStart) <= std::min(yEnd, b.yEnd);
		}
	};
}

std::string DayTwentytwo::runChallange()
{
	std::string line;

	std::vector<Block> bV;

	while (std::getline(inputManager->file, line))
	{
		Block b;

		auto str = split(line, "~");

		auto p1 = split(str.at(0), ",");

		b.xStart = std::stoi(p1[0]);
		b.yStart = std::stoi(p1[1]);
		b.zStart = std::stoi(p1[2]);

		auto p2 = split(str.at(1), ",");

		b.xEnd = std::stoi(p2[0]);
		b.yEnd = std::stoi(p2[1]);
		b.zEnd = std::stoi(p2[2]);

		bV.push_back(b);
	}

	std::sort(bV.begin(), bV.end(), [](const auto& a1, const auto& a2)
		{
			return a1.zStart < a2.zStart;
		});

	for (int i = 0; i < bV.size(); i++)
	{
		int maxZ = 1;

		for (int j = 0; j < i; j++)
		{
			if (bV[i].interSect(bV[j]))
			{
				maxZ = std::max(maxZ, bV[j].zEnd + 1);
			}
		}

		bV[i].zEnd -= bV[i].zStart - maxZ;
		bV[i].zStart = maxZ;
		
	}

	std::sort(bV.begin(), bV.end(), [](const auto& a1, const auto& a2)
		{
			return a1.zStart < a2.zStart;
		});

	std::unordered_map<int, int> blockSupport;
	std::unordered_map<int,std::vector<int>> blockSupportedBy;

	for (int upper = 0; upper < bV.size(); upper++)
	{
		for (int lower = 0; lower < upper; lower++)
		{
			if (bV[upper].interSect(bV[lower]) && bV[upper].zStart == bV[lower].zEnd + 1)
			{
				blockSupportedBy[upper].push_back(lower);
				blockSupport[lower]++;
			}
		}
	}

	auto allTrue = [&blockSupport](const std::vector<int>& v)
	{
		for (int i : v)
		{
			if (blockSupport[i] < 2)
				return 0;
		}
		return 1;
	};

	int totRes = 0;

	for (int i = 0; i < bV.size(); i++)
	{
		totRes += allTrue(blockSupportedBy[i]);
	}

	return std::to_string(totRes);
}

std::string DayTwentytwo::runChallangePart2()
{
	return "0";
}