#include "logManager.h"
#include <ServiceLocator/locator.h>
#include <Assets/assetManager.h>
#include <ECS/entity.h>
#include <iostream>
#include <algorithm>

LogManager::LogManager(Entity* screenLogOwner_) : screenLogsOwner(screenLogOwner_)
{
}

LogManager::~LogManager()
{
	logFileWriter.exit();
	logMessagesOnScreen.clear();

	Locator::provideLog(nullptr);
}


void LogManager::LogMessageToScreen(const std::string& logText, const Color& logColor, const float logDuration, const std::string logIndex)
{
	printLogToConsole(logText, LogCategory::Custom);
	displayLogToScreen(logText, LogCategory::Custom, logColor, logDuration, logIndex);
	writeLogToFile(logText, LogCategory::Custom);
}

void LogManager::EraseLogIndexMessage(const std::string logIndex)
{
	for (auto& screen_log : logMessagesOnScreen)
	{
		if (screen_log.hasSameIndex(logIndex))
		{
			screen_log.timer = 0.0f; //  mark for delete on next update
			break;
		}
	}
}

void LogManager::LogMessage_Category(const std::string& logText, LogCategory logCategory)
{
	printLogToConsole(logText, logCategory);
	displayLogToScreen(logText, logCategory, LogCategoryToColor(logCategory), 5.0f, "");
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


void LogManager::initialize()
{
	logFileWriter.init();
}

void LogManager::updateScreenLogs(float dt)
{
	std::vector<LogMessageScreen> expired_logs;

	for (auto& screen_log : logMessagesOnScreen)
	{
		screen_log.timer -= dt;
		if (screen_log.timer <= 0.0f) expired_logs.push_back(screen_log);
	}

	if (expired_logs.size() <= 0) return;

	for (auto& expired_log : expired_logs)
	{
		screenLogsOwner->removeComponent(expired_log.text);
		auto iter = std::find(logMessagesOnScreen.begin(), logMessagesOnScreen.end(), expired_log);
		logMessagesOnScreen.erase(iter);
	}
	logMessagesOnScreen.shrink_to_fit();
	expired_logs.clear();

	float next_y_offset = 0.0f;
	for (auto& screen_log : logMessagesOnScreen)
	{
		screen_log.yOffset = next_y_offset;
		screen_log.text->setPos(SCREEN_LOG_BASE_OFFSET + Vector2{ 0.0f, screen_log.yOffset });
		next_y_offset -= (screen_log.text->getSize().y + SCREEN_NEW_LOG_OFFSET);
	}
}


void LogManager::printLogToConsole(const std::string& logText, LogCategory logCategory)
{
	if (logCategory < logCategoryDisplayRules[LogDisplay::Console]) return;

	std::cout << LogCategoryToString(logCategory) << logText << std::endl;
}

void LogManager::displayLogToScreen(const std::string& logText, LogCategory logCategory, const Color& logColor, const float logDuration, const std::string logIndex)
{
	if (logCategory < logCategoryDisplayRules[LogDisplay::Screen]) return;

	for (auto& screen_log : logMessagesOnScreen)
	{
		if (screen_log.hasSameIndex(logIndex))
		{
			screen_log.text->setText(logText);
			screen_log.text->setTintColor(logColor);
			screen_log.timer = logDuration;
			return;
		}
	}

	//  screen log has not overriden another screen log, create new one
	float y_offset = 0.0f;
	if (logMessagesOnScreen.size() >= 1)
	{
		LogMessageScreen& screen_log = logMessagesOnScreen.at(logMessagesOnScreen.size() - 1);
		y_offset = screen_log.yOffset - screen_log.text->getSize().y - SCREEN_NEW_LOG_OFFSET;
	}

	logMessagesOnScreen.emplace_back(LogMessageScreen
		(
			logIndex,
			screenLogsOwner->addComponentByClass<TextRendererComponent>(),
			logDuration,
			y_offset
		)
	);

	logMessagesOnScreen.at(logMessagesOnScreen.size() - 1).text->setTextDatas(
		logText, 
		AssetManager::GetFont("arial_24"), 
		Vector2{ 0.0f, 1.0f }, 
		Vector2{ 0.0f, 1.0f }, 
		SCREEN_LOG_BASE_OFFSET + Vector2{ 0.0f, y_offset }, 
		Vector2{ 0.6f }, 
		0.0f, 
		logColor
	);
}

void LogManager::writeLogToFile(const std::string& logText, LogCategory logCategory)
{
	if (logCategory < logCategoryDisplayRules[LogDisplay::LogFile]) return;

	logFileWriter.addMessage(LogCategoryToString(logCategory) + logText);
}
