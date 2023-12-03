
#pragma once

#include "ICodeChallange.h"

class DaySixteen : public ICodeChallange
{
public:
	DaySixteen(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};