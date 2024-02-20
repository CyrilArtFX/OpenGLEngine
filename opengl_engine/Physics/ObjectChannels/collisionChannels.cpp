#include "collisionChannels.h"
#include <iostream>

std::unordered_map<std::string, std::vector<std::string>> CollisionChannels::registeredTestsChannels;

void CollisionChannels::RegisterTestChannel(std::string name, std::vector<std::string> testChannel)
{
	if (registeredTestsChannels.find(name) != registeredTestsChannels.end())
	{
		std::cout << "Collision Channels error. Tried to register a test channel with a name that already exists. Name is " << name << ".\n";
		return;
	}

	registeredTestsChannels.emplace(name, testChannel);
}

std::vector<std::string> CollisionChannels::GetRegisteredTestChannel(std::string name)
{
	if (registeredTestsChannels.find(name) == registeredTestsChannels.end())
	{
		std::cout << "Collision Channels error. Tried to get a registered test channel with a name that doesn't exists. Name is " << name << ".\n";
		return { "" };
	}

	return registeredTestsChannels.at(name);
}