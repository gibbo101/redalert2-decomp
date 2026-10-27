// void SidebarClass::Unknown_0067C150(ObjectClass *object) (0x0067C150)
// Redraws the active strip when an object of its kind appears that the
// player can build, or the fourth strip for buildings flagged at +0x1365.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
#include "shared/object.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F4F30@UnknownSidebarHouse@@QAE_NPAVTechnoTypeClass@@@Z=004f4f30
// @ref ?Unknown_004EB550@@YIHHH@Z=004eb550

void SidebarClass::Unknown_0067C150(ObjectClass *object)
{
    if (!unknown_4ee1 || !object) {
        return;
    }
    TechnoTypeClass *type = object->unknown_slot32();
    if (!unknown_player_a35db4) {
        return;
    }
    int kind = object->Kind_Of();
    int id = object->unknown_slot16();
    if (Which_Column(kind, id) == unknown_4ed8) {
        if (((UnknownSidebarHouse *)unknown_player_a35db4)->Unknown_004F4F30(type)) {
            Unknown_0067C100();
        }
    } else if (kind == 6 && ((UnknownSidebarBuilding *)object)->Type->unknown_1365) {
        Unknown_0067C310(3);
    }
}
