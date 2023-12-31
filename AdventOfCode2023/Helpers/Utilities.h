#pragma once

#include<vector>
#include<string>

namespace Util
{

	std::vector<std::string> split(std::string s, std::string delimiter);

	bool isInBounds(const std::pair<int, int>& pos, const std::vector<std::vector<char>>& matrix);

    int random(int start, int end);
}