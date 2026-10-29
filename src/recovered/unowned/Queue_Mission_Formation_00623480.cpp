// bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination, int speed, int maxspeed) (0x00623480): a MEGAMISSION_F event.
#include "shared/queue.hpp"
// @ref ??0EventClass@@QAE@HVTargetClass@@E00JJ@Z=004b61f0

bool __fastcall Queue_Mission(TargetClass whom, int mission, TargetClass const &target, TargetClass const &destination, int speed, int maxspeed)
{
    if (!OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, whom, mission, target, destination, speed, maxspeed))) {
        return false;
    }
    return true;
}
