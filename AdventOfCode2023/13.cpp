#include "13.h"

#include <iostream>
#include<unordered_map>
#include<unordered_set>

DayThirteen::DayThirteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}


bool isMirror(int l, int r, const std::vector<std::string>& pattern)
{
	while (l >= 0 && r < pattern.size())
	{
		if (pattern.at(l) != pattern.at(r))
			return false;

		l--;
		r++;
	}
	return true;
}

int findMirrorIndex(const std::vector<std::string>& pattern)
{
	for (int i = 0; i < pattern.size() - 1; i++)
	{
		if (pattern.at(i) == pattern.at(i + 1))
		{
			if (isMirror(i - 1, i + 2, pattern))
			{
				return i + 1;
			}
		}
	}
	return 0;
}


int findDiff(const std::string& l, const std::string& r)
{
	int diff = 0;
	for (int i = 0; i < l.size(); i++)
	{
		if (l.at(i) != r.at(i))
			diff++;
	}
	return diff;
}

bool isMirrorPart2(int l, int r, const std::vector<std::string>& pattern, bool smudgeUsed)
{
	while (l >= 0 && r < pattern.size())
	{
		int diff = findDiff(pattern.at(l), pattern.at(r));
		if (diff >= 1)
		{
			if (diff == 1 && !smudgeUsed)
				smudgeUsed = true;
			else
				return false;
		}

		l--;
		r++;
	}
	return smudgeUsed;
}

int findMirrorIndexPart2(const std::vector<std::string>& pattern)
{
	for (int i = 0; i < pattern.size() - 1; i++)
	{
		int diff = findDiff(pattern.at(i), pattern.at(i + 1));
		bool smudgeUsed = diff == 1;
		if (diff <= 1)
		{
			if (isMirrorPart2(i - 1, i + 2, pattern, smudgeUsed))
			{
				return i + 1;
			}
		}
	}
	return 0;
}

std::string DayThirteen::runChallange()
{
	std::string line;

	std::vector<std::string> verticalPattern;
	std::vector<std::string> horizontalPattern;

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		if (verticalPattern.size() == 0)
		{
			for (char c : line)
			{
				verticalPattern.push_back("");
			}
		}

		if (line != "")
		{
			horizontalPattern.push_back(line);

			for (int i = 0; i < line.size(); i++)
			{
				verticalPattern[i] += line.at(i);
			}
		}
		else
		{
			int vertIndex = findMirrorIndex(verticalPattern);
			int horIndex = findMirrorIndex(horizontalPattern);

			result += vertIndex + horIndex * 100;

			verticalPattern = std::vector<std::string>();
			horizontalPattern = std::vector<std::string>();
		}
	}

	int vertIndex = findMirrorIndex(verticalPattern);
	int horIndex = findMirrorIndex(horizontalPattern);

	result += vertIndex + horIndex * 100;

	return std::to_string(result);
}

std::string DayThirteen::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	std::vector<std::string> verticalPattern;
	std::vector<std::string> horizontalPattern;

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		if (verticalPattern.size() == 0)
		{
			for (char c : line)
			{
				verticalPattern.push_back("");
			}
		}

		if (line != "")
		{
			horizontalPattern.push_back(line);

			for (int i = 0; i < line.size(); i++)
			{
				verticalPattern[i] += line.at(i);
			}
		}
		else
		{
			int vertIndex = findMirrorIndexPart2(verticalPattern);
			int horIndex = findMirrorIndexPart2(horizontalPattern);

			result += vertIndex + horIndex * 100;

			verticalPattern = std::vector<std::string>();
			horizontalPattern = std::vector<std::string>();
		}
	}

	int vertIndex = findMirrorIndexPart2(verticalPattern);
	int horIndex = findMirrorIndexPart2(horizontalPattern);

	result += vertIndex + horIndex * 100;

	return std::to_string(result);
}