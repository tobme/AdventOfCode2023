#include "25.h"

#include "Helpers/Utilities.h"
#include <iostream>
#include <unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>


using namespace Util;

DayTwentyfive::DayTwentyfive(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

struct Vertex
{
	std::string name;
	std::unordered_map<std::string, bool> egdes;
	std::vector<std::string> nameHelper;

	void initHName()
	{
		for (const auto& e : egdes)
		{
			nameHelper.push_back(e.first);
		}
	}
};

std::unordered_map<std::string, bool> egdesStatus;

int calcSize(std::unordered_map<std::string, Vertex>& vertexes, const std::string& vStart)
{
	std::queue<Vertex> queue;
	std::unordered_set<std::string> visited;

	queue.push(vertexes[vStart]);

	while (!queue.empty())
	{
		auto e = queue.front();
		queue.pop();

		visited.insert(e.name);

		for (const auto& s : e.egdes)
		{
			if (s.second && !visited.contains(s.first))
			{
				queue.push(vertexes[s.first]);
			}
		}
	}

	return visited.size();
}

long long convertToASCII(const std::string& s)
{
	long long res = 0;
	for (int i = 0; i < s.length(); i++)
	{
		res += (int)s[i];
	}

	return res;
}

std::string inactivate(std::unordered_map<std::string, Vertex>& vertexes, const std::vector<std::string>& vNameHelper)
{

	std::string vertexName;
	int rand;
	int rand2;
	std::string egdeName;
	do
	{
		rand = random(0, vertexes.size() - 1);

		vertexName = vNameHelper[rand];

		rand2 = random(0, vertexes[vertexName].egdes.size() - 1);

		egdeName = vertexes[vertexName].nameHelper[rand2];


	} while (!vertexes[vertexName].egdes[egdeName]);

	vertexes[vertexName].egdes[egdeName] = false;
	vertexes[egdeName].egdes[vertexName] = false;

	return vertexName + "-" + egdeName;
}

std::string DayTwentyfive::runChallange()
{
	std::string line;

	std::unordered_map<std::string, Vertex> vertexes;
	std::vector<std::string> vNameHelper;

	while (std::getline(inputManager->file, line))
	{
		auto components = split(line, " ");

		std::string vertexName = components.front();
		vertexName.pop_back();
		components.erase(components.begin());

		for (auto& s : components)
		{
			vertexes[vertexName].name = vertexName;
			vertexes[vertexName].egdes[s] = true;
			vertexes[s].egdes[vertexName] = true;
			vertexes[s].name = s;
		}
	}

	for (auto& v : vertexes)
	{
		vNameHelper.push_back(v.first);
		v.second.initHName();
	}

	std::pair<std::string, std::string> splitPair;

	std::unordered_set<long long> memory;

	while(true)
	{
		std::vector<std::string> inactiveEgdes;

		std::string fullId = "";

		for (int i = 0; i < 3; i++)
		{
			std::string id = inactivate(vertexes, vNameHelper);
			fullId += id;
			inactiveEgdes.push_back(id);
		}

		long long intId = convertToASCII(fullId);
		
		if (!memory.contains(intId))
		{
			memory.insert(intId);
			if (calcSize(vertexes, vNameHelper.front()) != vertexes.size())
			{
				auto splitId = split(inactiveEgdes.front(), "-");
				splitPair = { splitId[0], splitId[1] };
				break;
			}
		}

		for (auto& egdeId : inactiveEgdes)
		{
			auto splitId = split(egdeId, "-");

			vertexes[splitId[0]].egdes[splitId[1]] = true;
			vertexes[splitId[1]].egdes[splitId[0]] = true;
		}
	}

	auto size1 = calcSize(vertexes, splitPair.first);
	auto size2 = calcSize(vertexes, splitPair.second);

	auto res = size1 * size2;

	return std::to_string(res);
}

std::string DayTwentyfive::runChallangePart2()
{
	return "0";
}