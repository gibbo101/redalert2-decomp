// BuildingClass *FootClass::unknown_4c45b0() (0x004C45B0, body 0xA4 bytes:
// the frozen inventory splits it at the loop branch 0x004C463A)
// The first building next to the unit (the eight adjacent cells in facing
// order) whose type is Overpowerable and whose owner is the unit's.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/techno_map.hpp"
// @ref ?Unknown_004717B0@UnknownCellClass@@QAEPAVBuildingClass@@XZ=004717b0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70

BuildingClass *FootClass::unknown_4c45b0()
{
    for (int facing = 0; facing < 8; facing++) {
        Cell cell = AdjacentCell[facing & 7] + unknown_slot104();
        BuildingClass *building = Map_Cell_At(cell)->Unknown_004717B0();
        if (building != 0 && building->Type->Overpowerable && building->Owning_House() == Owning_House()) {
            return building;
        }
    }
    return 0;
}
