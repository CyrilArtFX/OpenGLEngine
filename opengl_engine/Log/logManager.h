#pragma once
#include <ServiceLocator/log.h>
#include "logUtils.h"
#include <unordered_map>
#include <vector>

struct LogMessageScreen
{
	std::uint32_t index;
	std::string text;
	Color color;
	float timer;
	int yOffset;

	bool hasSameIndex(const std::uint32_t otherIndex) const
	{
		return index != 0 && index == otherIndex;
	}
};


/**
* The log service provider class.
*/
class LogManager : public Log
{
public:
	~LogManager();

	void LogMessageToScreen(const std::string& logText, const Color& logColor, const float logDuration, const std::uint32_t logIndex = 0) override;
	void LogMessage_Category(const std::string& logText, LogCategory logCategory) override;

	void SetScreenLogDisplayRule(LogCategory logCategory) override;
	void SetConsoleLogDisplayRule(LogCategory logCategory) override;


private:
	void printLogToConsole(const std::string& logText, LogCategory logCategory);
	void writeLogToFile(const std::string& logText, LogCategory logCategory);

	std::unordered_map<LogDisplay, LogCategory> logCategoryDisplayRules
	{
		{ LogDisplay::Console, LogCategory::Warning },
		{ LogDisplay::Screen, LogCategory::Custom },
		{ LogDisplay::LogFile, LogCategory::Info }
	};

	std::vector<LogMessageScreen> logMessagesOnScreen;
};