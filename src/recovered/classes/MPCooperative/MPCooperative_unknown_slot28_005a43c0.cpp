// bool MPCooperative::unknown_slot28() -- 0x005A43C0
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/multiplayer_game_mode.hpp"
#include "shared/house.hpp"
#include "shared/debug_printf.hpp"
#include "shared/lobby.hpp"
// @ref ??_C@_0BH@BAIP@?$EA?$EA?$EA?$EA?5Making?5Alliances?6?$AA@=007e3678
// @ref ??_C@_0BG@DOKC@?$EA?$EA?$EA?$EA?5?5?5?5?5House1?5?$DN?5?$CFs?6?$AA@=007e3660
// @ref ??_C@_0BK@BPGO@?$EA?$EA?$EA?$EA?5?5?5?5?5?5?5?5?5House2?5?$DN?5?$CFs?6?$AA@=007e3644
// @ref ??_C@_0DF@ODDM@?$EA?$EA?$EA?$EA?5Making?5Allies?5of?5?$CFs?$CI?$CFd?1?$CFd?1?$CF@=007e360c

bool MPCooperative::unknown_slot28()
{
    Debug_Printf("@@@@ Making Alliances\n");
    for (int i = 0; i < Houses.Count(); i++) {
        HouseClass *first = Houses[i];
        Debug_Printf("@@@@     House1 = %s\n", Unknown_006FA120(first->UIName));
        if (!first->Type->MultiplayPassive && first->unknown_134) {
            for (int j = i + 1; j < Houses.Count(); j++) {
                HouseClass *second = Houses[j];
                Debug_Printf("@@@@         House2 = %s\n", Unknown_006FA120(second->UIName));
                if (!second->Type->MultiplayPassive && second->unknown_134) {
                    char *second_name = Unknown_006FA120(second->UIName);
                    char *first_name = Unknown_006FA120(first->UIName);
                    Debug_Printf("@@@@ Making Allies of %s(%d/%d/%d) and %s(%d/%d/%d)\n",
                        first_name, first->Type->House, first->Type->Side, first->Type->Color,
                        second_name, second->Type->House, second->Type->Side, second->Type->Color);
                    first->Make_Ally(second, false);
                    second->Make_Ally(first, false);
                }
            }
        }
    }
    return true;
}
