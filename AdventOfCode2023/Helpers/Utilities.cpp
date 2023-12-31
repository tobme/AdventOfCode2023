#include "Utilities.h"
#include <random>

namespace Util
{

	std::vector<std::string> split(std::string s, std::string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}

	bool isInBounds(const std::pair<int, int>& pos, const std::vector<std::vector<char>>& matrix)
	{
		return pos.first >= 0 &&
			pos.second >= 0 &&
			pos.first < matrix.size() &&
			pos.second < matrix.front().size();
	}

	int random(int start, int end)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(start, end);

		return dist6(rng);
	}
}