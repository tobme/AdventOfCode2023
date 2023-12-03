
#pragma once

#include "ICodeChallange.h"

class DayEighteen : public ICodeChallange
{
public:
	DayEighteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};