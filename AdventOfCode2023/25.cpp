#include "25.h"

#include "Helpers/Utilities.h"
#include <iostream>
#include <unordered_map>
#include<unordered_set>


using namespace Util;

DayTwentyfive::DayTwentyfive(const std::shared_ptr<InputManager> getInput) : ICodeChallange(getInput) {}

struct Egde
{
	std::string from;
	std::string to;

	std::string origFrom;
	std::string origTo;

};

struct Vertex
{
	std::string name;
	std::vector<Egde> egdes;
};



std::string DayTwentyfive::runChallange()
{
	std::string line;

	std::unordered_map<std::string, Vertex> vertexes;
	std::vector<std::string> vertexNames;

	while (std::getline(inputManager->file, line))
	{
		auto components = split(line, " ");

		std::string vertexName = components.front();
		vertexName.pop_back();
		components.erase(components.begin());

		vertexes[vertexName].name = vertexName;

		std::vector<Egde> egdes;

		for (auto& s : components)
		{
			vertexes[vertexName].egdes.push_back(Egde(vertexName, s, vertexName, s));
			vertexes[s].egdes.push_back(Egde(s, vertexName, s, vertexName));
			vertexes[s].name = s;
		}
	}

	for (const auto& s : vertexes)
	{
		vertexNames.push_back(s.first);
	}

	auto originalGraph = vertexes;

	auto egdeSize = [](const std::unordered_map<std::string, Vertex>& vertexes)
	{
		int calc = 0;
		for (const auto& v : vertexes)
		{
			for (const auto& ve : v.second.egdes)
			{
				calc++;

				if (calc > 3)
					return calc;
			}
		}
		return calc;
	};

	while (egdeSize(vertexes) != 3)
	{
		vertexes = originalGraph;

		while (vertexes.size() > 2)
		{
			int rand = random(0, vertexNames.size() - 1);

			auto& vertex = vertexes[vertexNames[rand]];

			int rand2 = random(0, vertex.egdes.size() - 1);

			auto to = vertexes[vertex.egdes[rand2].to];
			auto& from = vertexes[vertex.name];

			for (const auto& s : from.egdes)
			{
				auto it = std::find_if(vertexes[s.to].egdes.begin(), vertexes[s.to].egdes.end(), [&from](const auto& st)
					{
						return st.to == from.name;
					});

				it->to = to.name;
			}

			auto it = std::find_if(to.egdes.begin(), to.egdes.end(), [&to](const auto& st)
				{
					return st.to == to.name;
				});

			to.egdes.erase(it);

			vertexes.erase(to.name);
			vertexNames.erase(vertexNames.begin() + rand);
		}
	}


	return "0";
}

std::string DayTwentyfive::runChallangePart2()
{
	return "0";
}