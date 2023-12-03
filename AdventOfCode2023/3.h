
#pragma once

#include "ICodeChallange.h"

class DayThree : public ICodeChallange
{
public:
	DayThree(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};