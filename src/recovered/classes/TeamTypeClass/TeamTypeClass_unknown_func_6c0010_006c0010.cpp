// bool TeamTypeClass::unknown_func_6c0010(FootClass *foot, HouseClass *house) (0x006C0010)
// Whether the foot may join a team of this type (HouseClass::Can_Build_Team): it belongs to house, is alive
// and not in radio contact, in no team or in one of a lower priority, in an idle mission when it has one,
// recruitable by the team type's Autocreate flag (+0x379/+0x37A), and not a unit with a weapon and no
// +0x254 state (kind 2).
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
#include "shared/team_type.hpp"
#include "shared/team.hpp"
#include "shared/foot.hpp"
#include "shared/mission.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_594db0@MissionClass@@SI_NH@Z=00594db0

bool TeamTypeClass::unknown_func_6c0010(FootClass *foot, HouseClass *house)
{
    if ((foot->Team == 0 || this != foot->Team->Class) && foot->Strength > 0 && foot->unknown_7d && !foot->unknown_76
        && !foot->In_Radio_Contact() && foot->House == house) {
        if (foot->unknown_slot91() != -1) {
            if (!MissionClass::unknown_594db0(foot->unknown_slot91())) {
                return false;
            }
        }
        if ((foot->unknown_379 || Autocreate) && (foot->unknown_37a || !Autocreate)
            && (foot->Team == 0 || foot->Team->Class->Priority < Priority)) {
            if (foot->Kind_Of() == 2 && foot->unknown_slot231(0)->WeaponType != 0 && foot->unknown_254 == 0) {
                return false;
            }
            return true;
        }
    }
    return false;
}
