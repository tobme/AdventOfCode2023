
#pragma once

#include "ICodeChallange.h"

class DayTwo : public ICodeChallange
{
public:
	DayTwo(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};