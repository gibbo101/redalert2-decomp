// void __cdecl Unknown_005C2C80(int color, unsigned short const *format, ...) (0x005C2c80)
// Formats a line and adds it to the list 0x53f of the current dialog or of the nearest dialog below it that has one.
#include "shared/lobby.hpp"

void __cdecl Unknown_005C2C80(int color, unsigned short const *format, ...)
{
    unsigned short buffer[0x400];
    memset(buffer, 0, sizeof(buffer));
    vswprintf(buffer, format, (char *)(&format + 1));
    if (Unknown_00735B10() != 0) {
        HWND window = Unknown_00735B10();
        HWND list = GetDlgItem(window, 0x53f);
        while (list == 0) {
            window = (HWND)unknown_previous_key((int)window);
            if (window == 0) {
                return;
            }
            list = GetDlgItem(window, 0x53f);
        }
        Unknown_005C2DA0(color, buffer, list);
    }
}
