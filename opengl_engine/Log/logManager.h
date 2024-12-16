#pragma once
#include <ServiceLocator/log.h>
#include "logUtils.h"
#include <Rendering/Text/textRendererComponent.h>
#include <Maths/Vector2.h>
#include <unordered_map>
#include <vector>

struct LogMessageScreen
{
	std::uint32_t index;
	TextRendererComponent* text;
	float timer;
	float yOffset;

	bool hasSameIndex(const std::uint32_t otherIndex) const
	{
		return index != 0 && index == otherIndex;
	}

	bool operator==(const LogMessageScreen& other) const
	{
		return text == other.text;
	}
};


const Vector2 SCREEN_LOG_BASE_OFFSET{ 20.0f, -20.0f };
const float SCREEN_NEW_LOG_OFFSET{ 10.0f };


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


	//  for the engine class (which is the only class that have access to the full log manager)
	void initialize();
	void updateScreenLogs(float dt);


private:
	void printLogToConsole(const std::string& logText, LogCategory logCategory);
	void displayLogToScreen(const std::string& logText, LogCategory logCategory, const Color& logColor, const float logDuration, const std::uint32_t logIndex);
	void writeLogToFile(const std::string& logText, LogCategory logCategory);

	std::unordered_map<LogDisplay, LogCategory> logCategoryDisplayRules
	{
		{ LogDisplay::Console, LogCategory::Warning },
		{ LogDisplay::Screen, LogCategory::Custom },
		{ LogDisplay::LogFile, LogCategory::Info }
	};

	std::vector<LogMessageScreen> logMessagesOnScreen;
};