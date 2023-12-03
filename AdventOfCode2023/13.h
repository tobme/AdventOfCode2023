
#pragma once

#include "ICodeChallange.h"

class DayThirteen : public ICodeChallange
{
public:
	DayThirteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};