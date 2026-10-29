// void __fastcall unknown_format_time(wchar_t *buffer, int time) -- 0x00465C20
// Formats a game time in seconds with TXT_TIME_FORMAT_HOURS as hours, minutes and seconds;
// times of 100 hours or more show as 99:59:59. Does nothing without a buffer.
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
// @ref ??_C@_0BG@MFEO@TXT_TIME_FORMAT_HOURS?$AA@=007d156c
// @ref ??_C@_0BE@LFCN@D?3?2Ra2?2CampScor?4cpp?$AA@=007d1584
#include "shared/string_table.hpp"

void __fastcall unknown_format_time_465c20(wchar_t *buffer, int time)
{
    if (buffer) {
        if (time / 3600 > 99) {
            time = 359999;
        }
        int hours = time / 3600;
        time -= hours * 3600;
        int minutes = time / 60;
        time -= minutes * 60;
        swprintf(buffer, StringTable::Load_String("TXT_TIME_FORMAT_HOURS", 0, "D:\\Ra2\\CampScor.cpp", 102), hours, minutes, time);
    }
}
