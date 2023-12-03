
#pragma once

#include "ICodeChallange.h"

class DayOne : public ICodeChallange
{
public:
	DayOne(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};