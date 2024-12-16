#include "logManager.h"
#include <ServiceLocator/locator.h>
#include <iostream>

LogManager::~LogManager()
{
	LogMessage_Category("Log Manager destroyed.", LogCategory::Info);

	logMessagesOnScreen.clear();

	Locator::provideLog(nullptr);
}

void LogManager::LogMessageToScreen(const std::string& logText, const Color& logColor, const float logDuration, const std::uint32_t logIndex)
{
	printLogToConsole(logText, LogCategory::Custom);
	writeLogToFile(logText, LogCategory::Custom);
}

void LogManager::LogMessage_Category(const std::string& logText, LogCategory logCategory)
{
	printLogToConsole(logText, logCategory);
	writeLogToFile(logText, logCategory);
}

void LogManager::SetScreenLogDisplayRule(LogCategory logCategory)
{
	logCategoryDisplayRules[LogDisplay::Screen] = logCategory;
}

void LogManager::SetConsoleLogDisplayRule(LogCategory logCategory)
{
	logCategoryDisplayRules[LogDisplay::Console] = logCategory;
}

void LogManager::printLogToConsole(const std::string& logText, LogCategory logCategory)
{
	if (logCategory < logCategoryDisplayRules[LogDisplay::Console]) return;

	std::cout << LogCategoryToString(logCategory) << logText << std::endl;
}

void LogManager::writeLogToFile(const std::string& logText, LogCategory logCategory)
{
	if (logCategory < logCategoryDisplayRules[LogDisplay::LogFile]) return;

	// TODO: write log to file
}
