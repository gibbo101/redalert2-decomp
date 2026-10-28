// void Unknown_006F6380() (0x006F6380)
// Queues an event of type 3 naming the owner (slot 14) of the first selected object, when that owner is another
// house with flag +0x134, the player does not have +0x13D, and the multiplayer rules allow it.
#include "shared/uicmnds.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
// @ref ??0EventClass@@QAE@HHK@Z=004b6030

void Unknown_006F6380()
{
    if (unknown_objects_a40c60.Count() != 0 && !unknown_player_a35db4->unknown_13d) {
        if (unknown_objects_a40c60[0]->Owning_House() != unknown_player_a35db4 && unknown_objects_a40c60[0]->Owning_House()->unknown_134) {
            unsigned long owner = unknown_objects_a40c60[0]->Owner();
            if (unknown_game_mode_a3d298 != 0 && !(unknown_id_source_a3d290->unknown_000 & 0x400) && Rules->unknown_111d) {
                OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 3, owner));
            }
        }
    }
}
