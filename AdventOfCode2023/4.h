
#pragma once

#include "ICodeChallange.h"

class DayFour : public ICodeChallange
{
public:
	DayFour(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};