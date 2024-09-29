// Copyright 2024 - 2025, Fernando González Ruano (Fegor)
// SPDX-License-Identifier: mit

// Based on https://www.geeksforgeeks.org/logging-system-in-cpp/

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "log4cpp.h"

using namespace std;

bool Log4Cpp::enableConsole = true;
bool Log4Cpp::enableFile = true;
bool Log4Cpp::enableSyslog = false;
bool Log4Cpp::enableSystemd = false;

Log4Cpp::Log4Cpp()
{
	this->openLogFile();
}

Log4Cpp::~Log4Cpp()
{
	logFile.close();
}

void Log4Cpp::debug(const string &message)
{
	this->log(LogLevel::LOG_LEVEL_DEBUG, message);
}

void Log4Cpp::info(const string &message)
{
	this->log(LogLevel::LOG_LEVEL_INFO, message);
}

void Log4Cpp::warning(const string &message)
{
	this->log(LogLevel::LOG_LEVEL_WARNING, message);
}

void Log4Cpp::error(const string &message)
{
	this->log(LogLevel::LOG_LEVEL_ERROR, message);
}

void Log4Cpp::critical(const string &message)
{
	this->log(LogLevel::LOG_LEVEL_CRITICAL, message);
}

void Log4Cpp::log(const LogLevel level, const string &message)
{
	// Get current timestamp
	// TO DO: Do configurable
	time_t now = time(0);
	tm *timeinfo = localtime(&now);
	char timestamp[20];
	strftime(timestamp, sizeof(timestamp),
			 "%Y-%m-%d %H:%M:%S", timeinfo);

	ostringstream logEntry;
	logEntry << "[" << timestamp << "] "
			 << levelToString(level) << ": " << message
			 << endl;

	if (this->enableConsole)
		cout << logEntry.str();

	if (this->enableFile)
		if (logFile.is_open())
		{
			logFile << logEntry.str();
			logFile.flush();
		}

	if (this->enableSystemd)
	{
		string s = "MESSAGE=";
		s.append(logEntry.str());
		sd_journal_send(s.c_str(), "SD_JOURNAL_TEST=SEND", "PRIORITY=%i", level, NULL);
	}
}

void Log4Cpp::setEnableConsole(const bool enable)
{
	Log4Cpp::enableConsole = enable;
}

void Log4Cpp::setEnableFile(const bool enable)
{
	Log4Cpp::enableFile = enable;
}

void Log4Cpp::setEnableSyslog(const bool enable)
{
	Log4Cpp::enableSyslog = enable;
}

void Log4Cpp::setEnableSystemd(const bool enable)
{
	Log4Cpp::enableSystemd = enable;
}

/*
void Log4Cpp::setLogFile(const string filename)
{
	openLogFile(filename);
}
*/
/*
void Log4Cpp::setLogLevel(const LogLevel level)
{
	logLevel = level;
}
*/

LogLevel Log4Cpp::getLogLevel() const
{
	return Log4Cpp::logLevel;
}

void Log4Cpp::openLogFile()
{
	logFile.open(this->fileName, ios::app);

	if (!logFile.is_open())
	{
		cerr << "Error opening log file: " << this->fileName << endl;
		exit(1);
	}
}

bool Log4Cpp::isDebugEnabled()
{
	return this->logLevel == LogLevel::LOG_LEVEL_DEBUG;
}

bool Log4Cpp::isInfoEnabled()
{
	return this->logLevel == LogLevel::LOG_LEVEL_INFO;
}

bool Log4Cpp::isWarningEnabled()
{
	return this->logLevel == LogLevel::LOG_LEVEL_WARNING;
}

bool Log4Cpp::isErrorEnabled()
{
	return this->logLevel == LogLevel::LOG_LEVEL_ERROR;
}

bool Log4Cpp::isCriticalEnabled()
{
	return this->logLevel == LogLevel::LOG_LEVEL_CRITICAL;
}

const string Log4Cpp::levelToString(const LogLevel level) const
{
	switch (level)
	{
	case LogLevel::LOG_LEVEL_DEBUG:
		return "DEBUG";
	case LogLevel::LOG_LEVEL_INFO:
		return "INFO";
	case LogLevel::LOG_LEVEL_WARNING:
		return "WARNING";
	case LogLevel::LOG_LEVEL_ERROR:
		return "ERROR";
	case LogLevel::LOG_LEVEL_CRITICAL:
		return "CRITICAL";
	default:
		return "UNKNOWN";
	}
}

// For testing
int main()
{
	Log4Cpp logger;

	Log4Cpp::fileName = "prueba.log";
	Log4Cpp::logLevel = LogLevel::LOG_LEVEL_ERROR;

	if (logger.isInfoEnabled())
	{
		logger.info("Info.");
	}
	else if (logger.isDebugEnabled())
	{
		logger.debug("Debug.");
	}
	else if (logger.isErrorEnabled())
	{
		logger.error("Error.");
	}
	else
	{
		logger.critical("Critical.");
	}

	return 0;
}
