
#pragma once

#include "ICodeChallange.h"

class DayTwelve : public ICodeChallange
{
public:
	DayTwelve(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};