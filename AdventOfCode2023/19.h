
#pragma once

#include "ICodeChallange.h"

class DayNineteen : public ICodeChallange
{
public:
	DayNineteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};