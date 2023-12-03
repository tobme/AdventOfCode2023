
#pragma once

#include "ICodeChallange.h"

class DayFifteen : public ICodeChallange
{
public:
	DayFifteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};