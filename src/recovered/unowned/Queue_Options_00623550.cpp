// bool __fastcall Queue_Options() (0x00623550): an OPTIONS event unless the player is out.
#include "shared/queue.hpp"
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0

bool __fastcall Queue_Options()
{
    if (unknown_player_a35db4->unknown_13f || unknown_player_a35db4->unknown_140 || unknown_player_a35db4->unknown_13e) {
        return false;
    }
    if (!OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x0C))) {
        return false;
    }
    return true;
}
