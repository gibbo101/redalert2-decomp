// bool MultiplayerGameMode::unknown_slot26() -- 0x005B7820
// Slot 26: clears flag 0x400 of the scenario (0x00A3D290); true.
#include "shared/abstract.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

bool MultiplayerGameMode::unknown_slot26()
{
    unknown_id_source_a3d290->unknown_000 &= ~0x400;
    return true;
}
