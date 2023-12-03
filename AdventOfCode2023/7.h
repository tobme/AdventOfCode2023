
#pragma once

#include "ICodeChallange.h"

class DaySeven : public ICodeChallange
{
public:
	DaySeven(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};