// void __fastcall Unknown_005c3b70() (0x005C3B70)
// Game mode 3 sends the players packet 0x28 (0x005C3AE0); game mode 4 runs 0x0075C960.
#include "shared/lobby.hpp"
// @ref ?Unknown_0075c960@@YAXXZ=0075c960

void __fastcall Unknown_005c3b70()
{
    switch (unknown_game_mode_a3d298) {
    case 3:
        Unknown_005c3ae0();
        break;
    case 4:
        Unknown_0075c960();
        break;
    }
}
