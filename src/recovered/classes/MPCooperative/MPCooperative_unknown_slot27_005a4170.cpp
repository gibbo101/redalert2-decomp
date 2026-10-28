// bool MPCooperative::unknown_slot27(bool official) -- 0x005A4170
// Gives every playing (not passive) house a start cell from the multiplayer start waypoints
// (slot 42 picks it) and centres its base there.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
// @ref ??_C@_0CN@PHGH@Assigning?5Starting?5Points?5for?5ho@=007e3584
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??_G?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
#include "shared/multiplayer_game_mode.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/id_source.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_memory.hpp"

bool MPCooperative::unknown_slot27(bool official)
{
    DynamicVectorClass<Cell> waypoints = Multiplayer_Start_Waypoints_0065fff0(official);
    bool taken[16];
    memset(taken, 0, sizeof(taken));
    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *house = Houses[i];
        if (!house->Type->MultiplayPassive) {
            Debug_Printf("Assigning Starting Points for house %d (%s)\n", i, (char const *)house->Type->ID);
            Cell cell = unknown_slot42(i, waypoints, taken);
            house->BaseCenter = CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
        }
    }
    return true;
}
