// void __fastcall Unknown_006F62D0(unsigned long argument) (0x006F62D0)
#include "shared/uicmnds.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
// @ref ??0EventClass@@QAE@HHK@Z=004b6030

void __fastcall Unknown_006F62D0(unsigned long argument)
{
    if (unknown_game_mode_a3d298 != 0 && !(unknown_id_source_a3d290->unknown_000 & 0x400) && Rules->unknown_111d) {
        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 3, argument));
    }
}
