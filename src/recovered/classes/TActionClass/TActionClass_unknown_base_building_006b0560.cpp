// bool TActionClass::unknown_base_building(...) (0x006B0560)
// Red Alert's TACTION_BASE_BUILDING: sets or clears the house's base-building flag (+0x13B); when set, the base
// centre and the base plan's cell move to the cell of the house's first building of the list at +0x50, and an
// empty base plan is filled (0x004F5BE0); always true.
#include "shared/taction.hpp"
#include "shared/house.hpp"
#include "shared/building.hpp"
// @ref ?unknown_func_4f5be0@HouseClass@@QAEXXZ=004f5be0

bool TActionClass::unknown_base_building(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (DataBool) {
        house->unknown_13b = true;
        if (house->unknown_50.Count() > 0) {
            CoordStruct coord = house->unknown_50[0]->Coord;
            Cell center = Coord_Cell(coord);
            house->BaseCenter = Cell_Center(center);
            house->unknown_55f0.unknown_50 = center;
        }
        if (house->unknown_55f0.Nodes.Count() == 0) {
            house->unknown_func_4f5be0();
        }
    } else {
        house->unknown_13b = false;
    }
    return true;
}
