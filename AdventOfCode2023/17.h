
#pragma once

#include "ICodeChallange.h"

class DaySeventeen : public ICodeChallange
{
public:
	DaySeventeen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};