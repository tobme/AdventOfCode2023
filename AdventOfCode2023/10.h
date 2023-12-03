
#pragma once

#include "ICodeChallange.h"

class DayTen : public ICodeChallange
{
public:
	DayTen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};