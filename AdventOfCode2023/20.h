
#pragma once

#include "ICodeChallange.h"

class DayTwenty : public ICodeChallange
{
public:
	DayTwenty(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};