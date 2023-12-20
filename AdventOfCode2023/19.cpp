#include "19.h"

#include <iostream>
#include<unordered_map>
#include "Helpers/Range.h"
#include "Helpers/Utilities.h"

DayNineteen::DayNineteen(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

class Rule
{
public:
	Rule(char _l, char _s, int _v, const std::string& _d) : letter(_l), sign(_s), value(_v), destination(_d) {}

	bool tryUpdateRanges(Range<int>& range, Range<int>* out)
	{
		if (sign == '<')
		{
			if (value > range.start)
			{
				out->start = range.start;
				out->end = value - 1;
				range.start = value;
				return true;
			}
		}
		else
		{
			if (value < range.end)
			{
				out->start = value + 1;
				out->end = range.end;
				range.end = value;
				return true;
			}
		}
		return false;
	}

	char letter;
	char sign;
	int value;
	std::string destination;
};

class RuleSet
{
public:
	RuleSet() = default;

	RuleSet(const std::string& _finalDest) : ruleset(), finalDest(_finalDest)
	{
	}

	void addRule(const Rule& r)
	{
		ruleset.push_back(r);
	}

	std::string testRules(std::unordered_map<char, int>& ratings)
	{
		for (const auto& r : ruleset)
		{
			auto v = ratings[r.letter];

			bool res = r.sign == '<' ? v < r.value : v > r.value;

			if (res)
				return r.destination;
		}

		return finalDest;
	}

	const std::string& getFinalDest() const
	{
		return finalDest;
	}

	std::vector<Rule> ruleset;
	std::string finalDest;
};

std::string doWorkflow(const std::string& currentWorkFlow, std::unordered_map<char, int> ratings, std::unordered_map<std::string, RuleSet>& workflow)
{
	if (currentWorkFlow == "A" || currentWorkFlow == "R")
	{
		return currentWorkFlow;
	}

	auto ruleset = workflow[currentWorkFlow];

	auto newWorkFlow = ruleset.testRules(ratings);

	return doWorkflow(newWorkFlow, ratings, workflow);
}

std::string DayNineteen::runChallange()
{
	std::string line;

	std::unordered_map<std::string, RuleSet> workflow;

	while (std::getline(inputManager->file, line))
	{
		if (line == "")
			break;

		auto startRuleIndex = line.find_first_of('{');

		auto name = line.substr(0, startRuleIndex);

		auto rules = line.substr(startRuleIndex + 1, line.size() - 2);

		auto rulesV = split(rules, ",");

		auto finalDest = rulesV.back();
		finalDest.pop_back();
		rulesV.pop_back();

		auto ruleSet = RuleSet(finalDest);

		for (const auto& s : rulesV)
		{
			char letter = s[0];
			char sign = s[1];

			auto vEnd = s.find_first_of(':');

			auto value = std::stoi(s.substr(2, vEnd));

			auto dest = s.substr(vEnd + 1);

			ruleSet.addRule(Rule(letter, sign, value, dest));
		}

		workflow[name] = ruleSet;
	}

	int result = 0;

	while (std::getline(inputManager->file, line))
	{
		auto instr = line.substr(1, line.size() - 2);

		auto instrV = split(instr, ",");


		std::unordered_map<char, int> ratings;

		for (const auto& s : instrV)
		{
			ratings[s[0]] = std::stoi(s.substr(2));
		}

		auto r = doWorkflow("in", ratings, workflow);

		if (r == "A")
		{
			result += ratings['x'] + ratings['m'] + ratings['a'] + ratings['s'];
		}
	}

	return std::to_string(result);
}

std::unordered_map<std::string, unsigned long long> memory;

unsigned long long doWorkFlowP2(const std::string& currentWorkFlow, std::unordered_map<std::string, RuleSet>& workflow, std::unordered_map<char, Range<int>> ranges)
{
	if (currentWorkFlow == "A")
	{
		return (unsigned long long)(ranges['x'].getLength() + 1) * (unsigned long long)(ranges['m'].getLength() + 1) * (unsigned long long)(ranges['a'].getLength() + 1) * (unsigned long long)(ranges['s'].getLength() + 1);
	}
	else if (currentWorkFlow == "R")
	{
		return 0;
	}
	else
	{
		if (memory.contains(currentWorkFlow))
		{
			return memory[currentWorkFlow];
		}

		auto rules = workflow[currentWorkFlow];

		auto ruleSet = rules.ruleset;

		unsigned long long finalRes = 0;

		for (auto& r : ruleSet)
		{
			auto l = r.letter;

			auto tmpRanges = ranges;
			bool success = r.tryUpdateRanges(ranges[l], &tmpRanges[l]);
			if (success)
			{
				finalRes += doWorkFlowP2(r.destination, workflow, tmpRanges);
			}
		}

		finalRes += doWorkFlowP2(rules.getFinalDest(), workflow, ranges);

		memory[currentWorkFlow] = finalRes;

		return finalRes;
	}
}

std::string DayNineteen::runChallangePart2()
{
	inputManager->resetStream();

	std::string line;

	std::unordered_map<std::string, RuleSet> workflow;

	while (std::getline(inputManager->file, line))
	{
		if (line == "")
			break;

		auto startRuleIndex = line.find_first_of('{');

		auto name = line.substr(0, startRuleIndex);

		auto rules = line.substr(startRuleIndex + 1, line.size() - 2);

		auto rulesV = split(rules, ",");

		auto finalDest = rulesV.back();
		finalDest.pop_back();
		rulesV.pop_back();

		auto ruleSet = RuleSet(finalDest);

		for (const auto& s : rulesV)
		{
			char letter = s[0];
			char sign = s[1];

			auto vEnd = s.find_first_of(':');

			auto value = std::stoi(s.substr(2, vEnd));

			auto dest = s.substr(vEnd + 1);

			ruleSet.addRule(Rule(letter, sign, value, dest));
		}

		workflow[name] = ruleSet;
	}
	unsigned long long res = 0;

	std::unordered_map<char, Range<int>> ranges = { {'x', Range(1, 4000)}, {'m', Range(1, 4000)}, {'a', Range(1, 4000)}, {'s', Range(1, 4000)} };

	res += doWorkFlowP2("in", workflow, ranges);


	return std::to_string(res);
}