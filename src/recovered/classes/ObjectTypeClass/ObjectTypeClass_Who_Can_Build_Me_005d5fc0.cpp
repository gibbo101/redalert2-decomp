// BuildingClass *ObjectTypeClass::Who_Can_Build_Me(bool in_theory, bool legal, bool check_limit, HouseClass *house) const (0x005D5FC0, slot 37)
// Scans the house's buildings for a factory of this type's kind that is
// out of limbo, not being sold (mission 0x13), owned by an allowed house
// and, as asked, powered (legal) and below the build limit (check_limit).
// Aircraft (kind 3) not built "in theory" need a helipad with a free radio
// slot; a naval unit type (kind 0x28) needs a naval yard and others a land
// factory. A primary factory (+0x32B) wins at once, else the last match.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/techno.hpp"
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Unknown_00636EA0@RadioClass@@QBE_NXZ=00636ea0
// @ref ?unknown_4e3660@HouseClass@@QAEHPBVTechnoTypeClass@@HH@Z=004e3660

// BuildingClass members not in the shared stub (hypothesis names).
struct UnknownBuildingView530 {
    char unknown_000[0x530];
    bool unknown_530;                   // +0x530 powered (hypothesis)
};

// BuildingTypeClass beyond TechnoTypeClass (the full layout is not shared
// yet): Factory (+0xC44), the kind of type it produces.
class UnknownBuildingTypeView : public TechnoTypeClass {
public:
    char unknown_b90[0xC44 - 0xB90];
    int Factory;                        // +0xC44
};

BuildingClass *ObjectTypeClass::Who_Can_Build_Me(bool in_theory, bool legal, bool check_limit, HouseClass *house) const
{
    BuildingClass *anybuilding = 0;
    int ownable = unknown_slot28();
    int count = house->Buildings.Count();
    for (int index = 0; index < count; index++) {
        BuildingClass *building = house->Buildings[index];
        if (building->unknown_76) {
            continue;
        }
        if (((UnknownBuildingTypeView *)building->Type)->Factory != Kind_Of()) {
            continue;
        }
        if (legal && !((UnknownBuildingView530 *)building)->unknown_530) {
            continue;
        }
        if (building->unknown_slot91() == 0x13 || building->MissionQueue == 0x13) {
            continue;
        }
        if (check_limit && building->House->unknown_4e3660((TechnoTypeClass const *)this, 1, 1) <= 0) {
            continue;
        }
        if ((((UnknownBuildingTypeView *)building->Type)->unknown_slot28() & ownable) == 0) {
            continue;
        }
        if (!in_theory && building->In_Radio_Contact() && Kind_Of() == 3) {
            if (Kind_Of() == 3 && building->Unknown_00636EA0()) {
                if (building->unknown_32b) {
                    return building;
                }
                anybuilding = building;
            }
            continue;
        }
        if (Kind_Of() == 0x28 && ((TechnoTypeClass const *)this)->Naval) {
            if (!((UnknownBuildingTypeView *)building->Type)->Naval) {
                continue;
            }
            if (building->unknown_32b) {
                return building;
            }
        } else if (((UnknownBuildingTypeView *)building->Type)->Naval) {
            continue;
        }
        if (building->unknown_32b) {
            return building;
        }
        anybuilding = building;
    }
    if (anybuilding != 0) {
        return anybuilding;
    }
    return 0;
}
