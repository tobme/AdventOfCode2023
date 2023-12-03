
#pragma once

#include "ICodeChallange.h"

class DayFive : public ICodeChallange
{
public:
	DayFive(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};