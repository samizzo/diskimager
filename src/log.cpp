#include "stdafx.h"
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include "log.h"

static FILE* s_logFile = nullptr;

void Log_Open()
{
    fopen_s(&s_logFile, "diskimager.log", "w");

    SYSTEMTIME localTime;
    GetLocalTime(&localTime);
    Log_Info("=== Log opened on %02d:%02d %02d/%02d/%04d ===\n", localTime.wHour, localTime.wMinute, localTime.wDay, localTime.wMonth, localTime.wYear);
}

void Log_Info(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (s_logFile)
    {
        fprintf_s(s_logFile, "INFO: ");
        vfprintf_s(s_logFile, fmt, args);
    }

    int len = _vscprintf(fmt, args) + 1;
    std::string msg;
    msg.resize(len);
    vsprintf_s(&msg[0], len, fmt, args);
    OutputDebugStringA("INFO: ");
    OutputDebugStringA(msg.c_str());

    va_end(args);
}

void Log_Close()
{
    SYSTEMTIME localTime;
    GetLocalTime(&localTime);
    Log_Info("=== Log closed on %02d:%02d %02d/%02d/%04d ===\n", localTime.wHour, localTime.wMinute, localTime.wDay, localTime.wMonth, localTime.wYear);

    if (s_logFile)
        fclose(s_logFile);
    s_logFile = nullptr;
}
