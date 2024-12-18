#include "logFile.h"
#include <ServiceLocator/locator.h>
#include <fstream>

void LogFile::addMessage(const std::string& message)
{
	logFileMessages.push_back(message);
}

void LogFile::writeMessagesToFile()
{
	std::ofstream log_file("log.txt");
	if (!log_file.is_open())
	{
		Locator::getLog().LogMessage_Category("Log File: Unable to write in log file.", LogCategory::Error);
		return;
	}

	for (auto& message : logFileMessages)
	{
		log_file << message << std::endl;
	}
	log_file.close();

	logFileMessages.clear();
}
