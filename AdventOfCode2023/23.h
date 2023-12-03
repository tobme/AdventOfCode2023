
#pragma once

#include "ICodeChallange.h"

class DayTwentythree : public ICodeChallange
{
public:
	DayTwentythree(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};