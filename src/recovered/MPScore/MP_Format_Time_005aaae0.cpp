// MP_Format_Time_005AAAE0 (0x005AAAE0): CampScor.cpp's unknown_format_time_467290 with its own source line.

void __fastcall MP_Format_Time_005AAAE0(wchar_t *buffer, int time)
{
    if (buffer) {
        if (time / 3600 > 99) {
            time = 359999;
        }
        int hours = time / 3600;
        time -= hours * 3600;
        int minutes = time / 60;
        time -= minutes * 60;
        swprintf(buffer, StringTable::Load_String("TXT_TIME_FORMAT_HOURS", 0, "D:\\Ra2\\MPScore.cpp", 129), hours, minutes, time);
    }
}
// @ref ??_C@_0BD@OOCG@D?3?2Ra2?2MPScore?4cpp?$AA@=007e55b8
// @ref ??_C@_0BG@MFEO@TXT_TIME_FORMAT_HOURS?$AA@=007d156c
// @ref ?Load_String@StringTable@@SIPBGPBDPAD0H@Z=006f9ec0
// @ref _swprintf=00783764
