#pragma once
#include <Log/logUtils.h>
#include <Utils/Color.h>
#include <string>

/**
* The Log Service class (the virtual class provided by the Locator).
*/
class Log
{
public:
	virtual ~Log() {}


	/**
	* Log a message to the screen (it will also log it to the console and the log file).
	* @param	logText			The text to log (supports \n).
	* @param	logColor		The color of the log text on screen.
	* @param	logDuration		The duration of the log message on the screen (in seconds). 0 means it will stay only for a frame.
	* @param	logIndex		The index of the log message. Writing another log message with the same index while this one is still on screen will override it. 0 means no index, the message can't be overriden (default).
	*/
	virtual void LogMessageToScreen(const std::string& logText, const Color& logColor, const float logDuration, const std::uint32_t logIndex = 0) = 0;

	/**
	* Log a message that follows the log category display rules.
	* @param	logText			The text to log (supports \n).
	* @param	logCategory		The category to log the message into.
	*/
	virtual void LogMessage_Category(const std::string& logText, LogCategory logCategory) = 0;

	/**
	* Set the display rule for the logs on the screen.
	* @param	logCategory		The lowest category log that can be displayed on the screen. Custom means that engine logs can't be displayed.
	*/
	virtual void SetScreenLogDisplayRule(LogCategory logCategory) = 0;

	/**
	* Set the display rule for the logs in the console.
	* @param	logCategory		The lowest category log that can be printed in the console. Custom means that engine logs can't be printed.
	*/
	virtual void SetConsoleLogDisplayRule(LogCategory logCategory) = 0;
};