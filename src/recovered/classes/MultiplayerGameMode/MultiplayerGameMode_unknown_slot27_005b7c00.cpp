// bool MultiplayerGameMode::unknown_slot27(bool official) -- 0x005B7C00
// Gives every non-passive house a start cell (slot 42 over the map's start waypoints) as its
// BaseCenter.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
// @ref ?Multiplayer_Start_Waypoints_0065fff0@@YI?AV?$DynamicVectorClass@VCell@@@@_N@Z=0065fff0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
// @ref ??_C@_0CN@ODLJ@Assigning?5Starting?5Points?5for?5ho@=007e3584
#include "shared/multiplayer_game_mode.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/coord.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

bool MultiplayerGameMode::unknown_slot27(bool official)
{
    DynamicVectorClass<Cell> cells = Multiplayer_Start_Waypoints_0065fff0(official);
    bool taken[16];
    memset(taken, 0, sizeof(taken));
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        if (!house->Type->MultiplayPassive) {
            Debug_Printf("Assigning Starting Points for house %d (%s)\n", index, (char const *)house->Type->ID);
            house->BaseCenter = Cell_Center(unknown_slot42(index, cells, taken));
        }
    }
    return true;
}
