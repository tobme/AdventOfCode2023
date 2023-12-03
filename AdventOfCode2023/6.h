
#pragma once

#include "ICodeChallange.h"

class DaySix : public ICodeChallange
{
public:
	DaySix(const std::shared_ptr<InputManager> getInput);
	std::string runChallange() override;
	std::string runChallangePart2() override;
};