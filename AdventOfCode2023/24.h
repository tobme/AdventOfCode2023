
#pragma once

#include "ICodeChallange.h"

class DayTwentyfour : public ICodeChallange
{
public:
	DayTwentyfour(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};