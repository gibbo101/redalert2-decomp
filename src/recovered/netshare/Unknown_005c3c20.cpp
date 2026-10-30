// void Unknown_005c3c20() (0x005C3C20)
// Sets the lobby flag 0x00A3FAB8 and runs the chat's (0x0075C980) or the LAN's (0x005C28E0) handler.
#include "shared/lobby.hpp"
// @ref ?Unknown_005c28e0@@YIXXZ=005c28e0
// @ref ?Unknown_0075c980@@YIXXZ=0075c980
// @ref ?unknown_lobby_flag_a3fab8@@3_NA=00a3fab8

void Unknown_005c3c20()
{
    unknown_lobby_flag_a3fab8 = true;
    if (unknown_chat_a72cfc != 0) {
        Unknown_0075c980();
    } else {
        Unknown_005c28e0();
    }
}
