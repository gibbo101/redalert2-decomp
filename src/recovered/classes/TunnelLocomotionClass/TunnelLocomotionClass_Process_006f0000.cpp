// bool __stdcall TunnelLocomotionClass::Process() (0x006F0000, ILocomotion 16)
// TibSun Tunnel.cpp Process: runs the dig cycle's state, drops an enemy unit's selection once
// it is shrouded or fogged and clears its damage particles. The state handlers expand inline
// (state 4's 0x006F0730 stays a call); their timer ratios then call the out-of-line
// CDTimerClass::Value 0x004A4D20 (inline budget: the two Object_Coord accessors are pending sites).
#include "shared/tunnel_locomotion.hpp"
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/special.hpp"
#include "shared/id_source.hpp"
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=004a4d20
// @ref ?unknown_6f0730@TunnelLocomotionClass@@QAEXXZ=006f0730

bool __stdcall TunnelLocomotionClass::Process()
{
    if (Is_Moving()) {
        int agl = LinkedTo->unknown_slot108();
        int height = LinkedTo->unknown_slot110();
        switch (unknown_18) {
        case 1:
            if (agl < 0) {
                unknown_18 = 3;
            } else {
                unknown_6f03b0();
            }
            break;
        case 2:
            if (agl < 0) {
                unknown_18 = 3;
            } else {
                unknown_6f0530();
            }
            break;
        case 3:
            if (height == -0x100) {
                LinkedTo->unknown_slot71(0);
                unknown_18 = 4;
            } else {
                unknown_6f0690();
            }
            break;
        case 4:
            unknown_6f0730();
            break;
        case 5:
            unknown_6f0aa0();
            break;
        case 6:
            unknown_6f0c50();
            break;
        case 7:
            unknown_6f0630();
            break;
        }
        if (LinkedTo->unknown_77) {
            if (!LinkedTo->House->Unknown_004F52B0()) {
                if (Map.Unknown_00568140(Object_Coord(LinkedTo)) || (unknown_id_source_a3d290->Special().FogOfWar && Map.Unknown_005683C0(Object_Coord(LinkedTo)))) {
                    LinkedTo->unknown_slot81();
                }
            }
        }
        LinkedTo->unknown_6d7f30();
        return true;
    }
    return false;
}
