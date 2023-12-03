
#pragma once

#include "ICodeChallange.h"

class DayTwentyfive : public ICodeChallange
{
public:
	DayTwentyfive(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};