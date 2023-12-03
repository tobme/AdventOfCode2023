
#pragma once

#include "Helpers/GetInput.h"

#include<string>
#include<memory>

class ICodeChallange
{
public:

	ICodeChallange(const std::shared_ptr<InputManager>& getInput) : inputManager(getInput){}

	virtual ~ICodeChallange() = default;

	virtual std::string runChallange() = 0;
	virtual std::string runChallangePart2() = 0;
protected:
	std::shared_ptr<InputManager> inputManager;
};