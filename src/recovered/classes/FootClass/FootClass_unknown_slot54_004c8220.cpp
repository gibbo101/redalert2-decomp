// void FootClass::unknown_slot54(bool arg1) (0x004C8220, slot 54)
// Detach_All (TibSun shape; hypothesis): a removal from the team, then the
// radio over-and-out (slot 149, message 3) when releasing or when the
// contact is not an ally.
#include "shared/foot.hpp"
#include "shared/house.hpp"
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@HH@Z=006b8fb0
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_slot54@ObjectClass@@UAEX_N@Z=005d3c10

void FootClass::unknown_slot54(bool arg1)
{
    if (arg1) {
        if (Team != 0 && unknown_a40774 == 0) {
            Team->Unknown_006B8FB0(this, -1, 0);
        }
    }
    if (!arg1) {
        TechnoClass *contact = Contact(0);
        if (contact != 0 && !House->Is_Ally(contact)) {
            unknown_slot149(3);
        }
    } else {
        unknown_slot149(3);
    }
    TechnoClass::unknown_slot54(arg1);
}
