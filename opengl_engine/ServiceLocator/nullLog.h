#pragma once
#include <ServiceLocator/log.h>

/**
* The log null service provider class.
*/
class NullLog : public Log
{
public:
	void LogMessageToScreen(const std::string& logText, const Color& logColor, const float logDuration, const std::uint32_t logIndex = 0) override {}
	void LogMessage_Category(const std::string& logText, LogCategory logCategory) override {}

	void SetScreenLogDisplayRule(LogCategory logCategory) override {}
	void SetConsoleLogDisplayRule(LogCategory logCategory) override {}
};