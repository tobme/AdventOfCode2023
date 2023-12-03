
#pragma once

#include "ICodeChallange.h"

class DayNine : public ICodeChallange
{
public:
	DayNine(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};