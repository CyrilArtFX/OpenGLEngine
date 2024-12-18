#pragma once
#include <vector>
#include <string>

class LogFile
{
public:
	void addMessage(const std::string& message);
	void writeMessagesToFile();

private:
	std::vector<std::string> logFileMessages;
};

