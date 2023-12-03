
#pragma once

#include "ICodeChallange.h"

class DayTwentyone : public ICodeChallange
{
public:
	DayTwentyone(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};