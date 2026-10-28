// bool MultiplayerSiege::unknown_slot27(bool official) -- 0x005AB770
// Gives the defending house (the session player on team 1) the first start cell and every
// other non-passive house a start cell from slot 42; false without a valid defender.
// @ref ?Multiplayer_Start_Waypoints_0065fff0@@YI?AV?$DynamicVectorClass@VCell@@@@_N@Z=0065fff0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ??_G?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ??_C@_0DH@KIP@Assigning?5Starting?5Points?5for?5De@=007e5700
// @ref ??_C@_0DH@JIL@Assigning?5Starting?5Points?5for?5At@=007e56c8
#include "shared/multiplayer_game_mode.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/coord.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"

bool MultiplayerSiege::unknown_slot27(bool official)
{
    DynamicVectorClass<Cell> cells = Multiplayer_Start_Waypoints_0065fff0(official);
    bool taken[16];
    memset(taken, 0, sizeof(taken));
    int index;
    for (index = 0; index < unknown_players_a3fa7c.Count(); index++) {
        if (unknown_players_a3fa7c[index]->Team == 1) {
            break;
        }
    }
    if (index >= unknown_players_a3fa7c.Count()) {
        return false;
    }
    int id = unknown_players_a3fa7c[index]->ID;
    if (id < 0 || id >= Houses.Count()) {
        return false;
    }
    HouseClass *defender = Houses[id];
    if (defender->Type->MultiplayPassive) {
        return false;
    }
    Debug_Printf("Assigning Starting Points for Defending house %d (%s)\n", id, (char const *)defender->Type->ID);
    Cell start = cells[0];
    taken[0] = true;
    defender->BaseCenter = Cell_Center(start);
    for (int house = 0; house < Houses.Count(); house++) {
        HouseClass *attacker = Houses[house];
        if (!attacker->Type->MultiplayPassive && attacker != defender) {
            Debug_Printf("Assigning Starting Points for Attacking house %d (%s)\n", house, (char const *)attacker->Type->ID);
            attacker->BaseCenter = Cell_Center(unknown_slot42(house, cells, taken));
        }
    }
    return true;
}
