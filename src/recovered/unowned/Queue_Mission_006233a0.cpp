// bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination) (0x006233A0): a MEGAMISSION event for the player.
#include "shared/queue.hpp"
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338

bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination)
{
    if (!OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, whom, mission, target, destination, TargetClass()))) {
        return false;
    }
    return true;
}
