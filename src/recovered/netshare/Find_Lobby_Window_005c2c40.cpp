// HWND Find_Lobby_Window_005c2c40() (0x005C2C40)
// The first of the dialogs 0xC2, 0xC9, 0xBC and 0xBD that is open, or 0.
#include "shared/lobby.hpp"

HWND Find_Lobby_Window_005c2c40()
{
    HWND window = Find_Dialog_00735940(0xc2);
    if (window == 0) {
        window = Find_Dialog_00735940(0xc9);
        if (window == 0) {
            window = Find_Dialog_00735940(0xbc);
            if (window == 0) {
                window = Find_Dialog_00735940(0xbd);
            }
        }
    }
    return window;
}
