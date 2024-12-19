#pragma once
#include <vector>
#include <string>
#include <fstream>

const std::string LOG_FILE{ "log.txt" };

class LogFile
{
public:
	void init();
	void exit();
	void addMessage(const std::string& message);

private:
	std::ofstream logFileStream;
};