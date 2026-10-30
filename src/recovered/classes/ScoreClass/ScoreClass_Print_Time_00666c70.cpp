// void ScoreClass::Print_Time(unsigned long seconds) (0x00666C70)
// Types the elapsed time as hh:mm:ss (at most 99:59:59), centred on 542.
#include "shared/score.hpp"
// @ref ?ScoreDelay@ScoreClass@@QAEXH@Z=00667420
// @ref ??_C@_1CE@DDLG@?$AA?$CF?$AA0?$AA2?$AAl?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAl?$AAd?$AA?3?$AA?$CF?$AA0?$AA2?$AAl?$AAd?$AA?$AA@=007f2a20
#include "shared/string_table.hpp"

void ScoreClass::Print_Time(unsigned long seconds)
{
    unsigned short buffer[20];
    if (seconds / 3600 > 99) {
        seconds = 359999;
    }
    unsigned long hours = seconds / 3600;
    seconds -= hours * 3600;
    unsigned long minutes = seconds / 60;
    seconds -= minutes * 60;
    swprintf((wchar_t *)buffer, L"%02ld:%02ld:%02ld", hours, minutes, seconds);
    int x = XOffset - unknown_font_10->String_Pixel_Width(buffer) / 2 + 542;
    ScorePrintClass *anim = new ScorePrintClass(buffer, x, YOffset + 322, unknown_font_10, false);
    Anims.Add(anim);
    while (Anims.ID(anim) != -1) {
        ScoreDelay(1);
    }
}
