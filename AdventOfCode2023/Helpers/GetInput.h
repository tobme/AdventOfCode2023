#pragma once

#include<string>
#include<fstream>

#include <vector>

using Matrix = std::vector<std::vector<char>>;

class InputManager
{
public:
	InputManager(const std::string& day);

	Matrix getMatrix();

	void resetStream();

	std::fstream file;
};