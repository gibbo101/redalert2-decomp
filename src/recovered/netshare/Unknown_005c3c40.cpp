// void Unknown_005c3c40() (0x005C3C40)
// Clears the lobby flag 0x00A3FAB8 and runs the chat's (0x0075CA00) or the LAN's (0x005C2940) handler.
#include "shared/lobby.hpp"
// @ref ?Unknown_005c2940@@YAXXZ=005c2940
// @ref ?Unknown_0075ca00@@YAXXZ=0075ca00
// @ref ?unknown_lobby_flag_a3fab8@@3_NA=00a3fab8

void Unknown_005c3c40()
{
    unknown_lobby_flag_a3fab8 = false;
    if (unknown_chat_a72cfc != 0) {
        Unknown_0075ca00();
    } else {
        Unknown_005c2940();
    }
}
