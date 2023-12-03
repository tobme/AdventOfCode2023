
#pragma once

#include "ICodeChallange.h"

class DayTwentytwo : public ICodeChallange
{
public:
	DayTwentytwo(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};