
#pragma once

#include "ICodeChallange.h"

class DayFourteen : public ICodeChallange
{
public:
	DayFourteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};