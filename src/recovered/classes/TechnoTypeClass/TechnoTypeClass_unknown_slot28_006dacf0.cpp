// int TechnoTypeClass::unknown_slot28() const (0x006DACF0)
// Who may own the type (hypothesis: RA1 Get_Ownable): every house when
// DoubleOwned in a non-zero game mode, else the Owner= house set.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

int TechnoTypeClass::unknown_slot28() const
{
    if (DoubleOwned && unknown_game_mode_a3d298) {
        return 0x7FFFFFFF;
    }
    return Owner;
}
