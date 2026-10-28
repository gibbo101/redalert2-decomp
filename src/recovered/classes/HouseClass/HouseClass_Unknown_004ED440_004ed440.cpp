// void HouseClass::Unknown_004ED440(TechnoClass *techno, bool sold) (0x004ED440)
// An object of the house leaves the map (TechnoClass slot 52): the sidebar
// strip is refreshed and its type uncounted by kind; a building also gives
// back its type's Storage and either pays out its stored tiberium (sold: the
// value times the house type's factor to the balance, five per unit to
// +0x5418) or takes it off the house's tiberium.
#include "shared/unit.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/tiberium.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Decrement@UnknownHouseCounter@@QAEXH@Z=00491cb0
// @ref ??ZStorageClass@@QAE?AV0@ABV0@@Z=0069afa0
// @ref ?Remove_Amount@StorageClass@@QAEMMH@Z=0069ae70
// @ref ?First_Used_Slot@StorageClass@@QBEHXZ=0069afe0
// @ref ?Unknown_0067C150@SidebarClass@@QAEXPAVObjectClass@@@Z=0067c150

void HouseClass::Unknown_004ED440(TechnoClass *techno, bool sold)
{
    Map.Unknown_0067C150(techno);
    switch (techno->Kind_Of()) {
    case 6:
        unknown_5460.Decrement(techno->unknown_slot32()->unknown_slot16());
        if (techno != 0) {
            BuildingClass *building = (BuildingClass *)techno;
            unknown_5668 = true;
            Capacity -= building->Type->Storage;
            if (sold) {
                StorageClass &storage = building->unknown_294;
                int type = storage.First_Used_Slot();
                while (type != -1) {
                    int amount = (int)storage.Remove_Amount(2147483648.0f, type);
                    unknown_5418 += amount * 5.0f;
                    Balance += unknown_TiberiumClass_list_00ac0b30[type]->Value * Type->unknown_0x148 * amount;
                    type = storage.First_Used_Slot();
                }
            } else {
                Tiberium -= building->unknown_294;
            }
        }
        break;
    case 2:
        unknown_5490.Decrement(techno->unknown_slot32()->unknown_slot16());
        break;
    case 15:
        unknown_5480.Decrement(techno->unknown_slot32()->unknown_slot16());
        break;
    case 1:
        unknown_5470.Decrement(techno->unknown_slot32()->unknown_slot16());
        break;
    }
}
