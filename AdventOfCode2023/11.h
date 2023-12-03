
#pragma once

#include "ICodeChallange.h"

class DayEleven : public ICodeChallange
{
public:
	DayEleven(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};