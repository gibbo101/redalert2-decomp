// void MultiplayerDebugCommandClass::Execute(int key) const -- 0x0051D7C0
// Toggles the multiplayer debug display (0x00A3D8C5) when debugging is
// allowed (0x00A3D8C4). Flag names are hypotheses.
#include "shared/command.hpp"
// @ref ?unknown_debug_allowed_a3d8c4@@3_NA=00a3d8c4
// @ref ?unknown_debug_display_a3d8c5@@3_NA=00a3d8c5

extern bool unknown_debug_allowed_a3d8c4;
extern bool unknown_debug_display_a3d8c5;

void MultiplayerDebugCommandClass::Execute(int key) const
{
    if (unknown_debug_allowed_a3d8c4) {
        unknown_debug_display_a3d8c5 = !unknown_debug_display_a3d8c5;
    }
}
