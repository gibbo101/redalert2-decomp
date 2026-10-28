// void __fastcall Build_Time_Text(char *buffer, int size) (0x00737A60)
// The build time stamp as "MM/DD/YYYY - hh:mm:ss" (buffer untouched if it does not convert).
#include "shared/win_stub.hpp"
#include "shared/wstring.hpp"

// @ref ?unknown_build_time_7d8940@@3UFILETIME@@B=007d8940
// @ref ??_C@_0CA@EOMK@?$CF02d?1?$CF02d?1?$CF04d?5?9?5?$CF02d?3?$CF02d?3?$CF02d?$AA@=007fd198

void __fastcall Build_Time_Text(char *buffer, int size)
{
    SYSTEMTIME time;
    if (FileTimeToSystemTime(&unknown_build_time_7d8940, &time)) {
        sprintf(buffer, "%02d/%02d/%04d - %02d:%02d:%02d", time.wMonth, time.wDay, time.wYear, time.wHour,
                time.wMinute, time.wSecond);
    }
}
