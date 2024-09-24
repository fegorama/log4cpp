// Copyright 2024 - 2025, Fernando González Ruano (Fegor)
// SPDX-License-Identifier: mit

#ifndef LOG4CPP_H
#define LOG4CPP_H

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <systemd/sd-journal.h>

using namespace std;

// Error leves same systemd/Journal
enum class LogLevel : int8_t
{
    LOG_LEVEL_EMERGENCY = 0, // not use
    LOG_LEVEL_ALERT = 1,     // not use
    LOG_LEVEL_CRITICAL = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_WARNING = 4,
    LOG_LEVEL_NOTICE = 5, // not use
    LOG_LEVEL_INFO = 6,
    LOG_LEVEL_DEBUG = 7
};

class Log4Cpp
{
public:
    Log4Cpp();
    ~Log4Cpp();
    void log(const LogLevel level, const string &message);
    void debug(const string &message);
    void info(const string &message);
    void warning(const string &message);
    void error(const string &message);
    void critical(const string &message);
    void setEnableConsole(const bool enable);
    void setEnableFile(const bool enable);
    void setEnableSyslog(const bool enable);
    void setEnableSystemd(const bool enable);

    // void setLogFile(const string filename);
    // void setLogLevel(const LogLevel level);
    LogLevel getLogLevel() const;
    bool isDebugEnabled();
    bool isInfoEnabled();
    bool isWarningEnabled();
    bool isErrorEnabled();
    bool isCriticalEnabled();

    static LogLevel logLevel;
    static string fileName;
    static bool enableConsole;
    static bool enableFile;
    static bool enableSyslog;
    static bool enableSystemd;

private:
    ofstream logFile;

    void openLogFile();
    const string levelToString(const LogLevel level) const;
};

#endif