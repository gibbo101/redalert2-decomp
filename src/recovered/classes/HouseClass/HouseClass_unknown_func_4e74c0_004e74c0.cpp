// TechnoTypeClass *HouseClass::unknown_func_4e74c0(int kind, bool naval) (0x004E74C0)
// The type kept per object kind at +0x553C..+0x5548 (an index into the
// type list of that kind; -1 for none).
#include "shared/techno.hpp"

// The type lists (declared by shared/aircraft_type.hpp, unit_type.hpp,
// infantry_type.hpp and building_type.hpp, which this unit's views of the
// object classes keep it from including).
class AircraftTypeClass;
class UnitTypeClass;
class InfantryTypeClass;
class BuildingTypeClass;
extern DynamicVectorClass<AircraftTypeClass *> AircraftTypes;       // 0x00A3D278
extern DynamicVectorClass<UnitTypeClass *> UnitTypes;               // 0x00A35D48
extern DynamicVectorClass<InfantryTypeClass *> InfantryTypes;       // 0x00A40350
extern DynamicVectorClass<BuildingTypeClass *> BuildingTypes;       // 0x00A35CD8

TechnoTypeClass *HouseClass::unknown_func_4e74c0(int kind, bool naval)
{
    switch (kind) {
    case 2:
    case 3:
        if (unknown_5548 != -1) {
            return (TechnoTypeClass *)AircraftTypes[unknown_5548];
        }
        break;
    case 1:
    case 40:
        if (unknown_5540 != -1) {
            return (TechnoTypeClass *)UnitTypes[unknown_5540];
        }
        break;
    case 15:
    case 16:
        if (unknown_5544 != -1) {
            return (TechnoTypeClass *)InfantryTypes[unknown_5544];
        }
        break;
    case 6:
    case 7:
        if (unknown_553c != -1) {
            return (TechnoTypeClass *)BuildingTypes[unknown_553c];
        }
        break;
    }
    return 0;
}
