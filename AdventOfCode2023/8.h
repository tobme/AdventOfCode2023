
#pragma once

#include "ICodeChallange.h"

class DayEight : public ICodeChallange
{
public:
	DayEight(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};