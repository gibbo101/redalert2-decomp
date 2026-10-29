// bool __fastcall Queue_Event_22() (0x00623600): a type 0x22 event unless the player is out (name hypothesis).
#include "shared/queue.hpp"
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0

bool __fastcall Queue_Event_22()
{
    if (unknown_player_a35db4->unknown_13f || unknown_player_a35db4->unknown_140 || unknown_player_a35db4->unknown_13e) {
        return false;
    }
    if (!OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x22))) {
        return false;
    }
    return true;
}
