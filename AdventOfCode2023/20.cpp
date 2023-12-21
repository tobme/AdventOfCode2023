#include "20.h"

#include <iostream>
#include<unordered_map>
#include<sstream>
#include<queue>
#include<set>
#include <numeric>
#include <map>
DayTwenty::DayTwenty(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

enum Pulse : int
{
	LOW = 0,
	HIGH = 1
};

class Module
{
public:
	Module(const std::string& _name, const std::vector<std::string>& _targets) : name(_name), targets(_targets)
	{

	}

	virtual ~Module() = default;

	virtual bool sendPulse(Pulse& pulse, const std::string& sender) = 0;

	std::vector<std::string> targets;
protected:
	std::string name;
};

class Broadcaster : public Module
{
public:
	Broadcaster(const std::string& _name, const std::vector<std::string>& _targets) : Module(_name, _targets)
	{
	}

	bool sendPulse(Pulse& pulse, const std::string& sender)
	{
		return true;
	}
};

class Flipflop : public Module
{
public:
	Flipflop(const std::string& _name, const std::vector<std::string>& _targets) : Module(_name, _targets), state(Pulse::LOW)
	{
	}

	bool sendPulse(Pulse& pulse, const std::string& sender)
	{
		if (pulse == Pulse::HIGH)
		{
			return false;
		}

		state = static_cast<Pulse>(!static_cast<int>(state));
		pulse = state;

		return true;
	}

private:
	Pulse state;
};

class Conjuction : public Module
{
public:
	Conjuction(const std::string& _name, const std::vector<std::string>& _targets) : Module(_name, _targets), pulses()
	{
	}

	void addPulses(const std::set<std::string>& s)
	{
		for (auto& a : s)
		{
			pulses[a] = Pulse::LOW;
		}
	}

	bool sendPulse(Pulse& pulse, const std::string& sender)
	{

		pulses[sender] = pulse;

		for (auto& p : pulses)
		{
			if (p.second == Pulse::LOW)
			{
				pulse = Pulse::HIGH;
				return true;
			}

		}
		pulse = Pulse::LOW;
		return true;
	}
private:
	std::unordered_map<std::string, Pulse> pulses;
};

struct PulseRequest
{
	std::string from;
	Pulse pulse;
	std::string to;
};

std::string DayTwenty::runChallange()
{
	std::string line;


	std::unordered_map<std::string, std::unique_ptr<Module>> modules;
	std::unordered_map<std::string, std::set<std::string>> inputs;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;
		ss >> line;

		char type = line[0];

		if (line[0] == '%' || line[0] == '&')
		{
			line.erase(0, 1);
		}

		std::string sender = line;
		ss >> line; // Skip arrow

		std::vector<std::string> receivers;

		while (ss >> line)
		{
			if (line.back() == ',')
			{
				line.pop_back();
			}

			inputs[line].insert(sender);

			receivers.push_back(line);
		}

		switch (type)
		{
		case '&':
			modules[sender] = std::make_unique<Conjuction>(sender, receivers);
			break;
		case '%':
			modules[sender] = std::make_unique<Flipflop>(sender, receivers);
			break;
		default:
			modules[sender] = std::make_unique<Broadcaster>(sender, receivers);
			break;
		}
	}

	for (auto& a : modules)
	{
		Conjuction* obj;
		if ((obj = dynamic_cast<Conjuction*>(a.second.get())) != nullptr)
		{
			obj->addPulses(inputs[a.first]);
		}
	}

	std::unordered_map<Pulse, int, std::hash<int>> pulseCounter;
	modules["button"] = std::make_unique<Broadcaster>("button", std::vector<std::string>{"broadcaster"});

	std::queue<PulseRequest> queue;

	for (int i = 0; i < 1000; i++)
	{
		queue.push(PulseRequest("start", Pulse::LOW, "button"));

		while (!queue.empty())
		{
			auto req = queue.front();
			queue.pop();

			if (modules.contains(req.to))
			{
				auto tmp = req.pulse;
				bool success = modules[req.to]->sendPulse(req.pulse, req.from);

				if (success)
				{
					auto receivers = modules[req.to]->targets;

					for (const auto& s : receivers) // SENDING
					{
						pulseCounter[req.pulse]++;

						queue.push(PulseRequest(req.to, req.pulse, s));
					}
				}
			}
		}
	}

	unsigned long long res = pulseCounter[Pulse::LOW] * pulseCounter[Pulse::HIGH];

	return std::to_string(res);
}

std::string DayTwenty::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;


	std::unordered_map<std::string, std::unique_ptr<Module>> modules;
	std::unordered_map<std::string, std::set<std::string>> inputs;

	while (std::getline(inputManager->file, line))
	{
		std::stringstream ss;
		ss << line;
		ss >> line;

		char type = line[0];

		if (line[0] == '%' || line[0] == '&')
		{
			line.erase(0, 1);
		}

		std::string sender = line;
		ss >> line; // Skip arrow

		std::vector<std::string> receivers;

		while (ss >> line)
		{
			if (line.back() == ',')
			{
				line.pop_back();
			}

			inputs[line].insert(sender);

			receivers.push_back(line);
		}

		switch (type)
		{
		case '&':
			modules[sender] = std::make_unique<Conjuction>(sender, receivers);
			break;
		case '%':
			modules[sender] = std::make_unique<Flipflop>(sender, receivers);
			break;
		default:
			modules[sender] = std::make_unique<Broadcaster>(sender, receivers);
			break;
		}
	}

	for (auto& a : modules)
	{
		Conjuction* obj;
		if ((obj = dynamic_cast<Conjuction*>(a.second.get())) != nullptr)
		{
			obj->addPulses(inputs[a.first]);
		}
	}

	modules["button"] = std::make_unique<Broadcaster>("button", std::vector<std::string>{"broadcaster"});

	std::queue<PulseRequest> queue;

	auto rec = inputs["rx"];

	auto receiversToEnd = inputs[*rec.begin()];

	std::vector<std::pair<std::string, int>> found;

	int res = 0;

	while (true)
	{
		queue.push(PulseRequest("start", Pulse::LOW, "button"));
		res++;

		while (!queue.empty())
		{
			auto req = queue.front();
			queue.pop();

			if (modules.contains(req.to))
			{
				auto tmp = req.pulse;
				bool success = modules[req.to]->sendPulse(req.pulse, req.from);

				if (success)
				{
					auto receivers = modules[req.to]->targets;

					for (const auto& s : receivers) // SENDING
					{
						if (s == "cs" && req.pulse == Pulse::HIGH)
						{
							found.push_back({ req.to, res });

							if (found.size() == receiversToEnd.size()) // All found
							{
								unsigned long long lcm = found.back().second;
								found.pop_back();

								for (auto res : found)
								{
									lcm = lcm * res.second / std::gcd(lcm, res.second);
								}
								return std::to_string(lcm);
							}
						}
						if (s == "rx" && req.pulse == Pulse::LOW)
						{
							return std::to_string(res);
						}

						queue.push(PulseRequest(req.to, req.pulse, s));
					}
				}
			}
		}
	}

	return "0";
}