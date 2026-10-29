// void Unknown_006F5C50() (0x006F5C50)
// The cheer command: once the rules' MaximumCheerRate frames have passed (and not while
// 0x00A3D548 is set), queues a cheer event (0x2D) for the player.
#include "shared/uicmnds.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_cheer_frame_ac134c@@3HA=00ac134c
// @ref ??0EventClass@@QAE@HE@Z=004b5fd0

void Unknown_006F5C50()
{
    if (Frame >= unknown_cheer_frame_ac134c && unknown_int_a3d548 == 0) {
        OutList.Add(EventClass(unknown_player_a35db4->ArrayIndex, 0x2D));
        unknown_cheer_frame_ac134c = Rules->MaximumCheerRate + Frame;
    }
}
