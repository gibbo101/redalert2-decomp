// bool HouseClass::unknown_func_4e7580(ObjectClass *object, bool arg2) (0x004E7580)
// Releases an object (a unit through 0x007049F0, anything else through its
// cell); forgets it at +0x5308 when it was kept there. With arg2 the marked
// cell at +0x530C is cleared too.
#include "shared/techno.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

// UnitClass and the cell object as far as this unit calls them (views).
struct UnknownUnitReleaseView {
    bool unknown_func_7049f0();             // 0x007049F0
};
struct UnknownCellView {
    char unknown_00[0x44];
    int unknown_44;                         // +0x44

    bool unknown_func_478720();             // 0x00478720
};


bool HouseClass::unknown_func_4e7580(ObjectClass *object, bool arg2)
{
    bool result = false;
    if (object != 0) {
        if (object->Kind_Of() == 1) {
            result = ((UnknownUnitReleaseView *)object)->unknown_func_7049f0();
            if (result && unknown_5308 == object) {
                unknown_5308 = 0;
            }
        } else {
            Cell cell = Coord_Cell(object->Center_Coord());
            if (Map.Unknown_0054AAB0(cell)) {
                result = ((UnknownCellView *)&Map[cell])->unknown_func_478720();
                if (result && unknown_5308 == object) {
                    unknown_5308 = 0;
                }
            }
        }
        if (arg2 && unknown_530c != unknown_geometry_k) {
            ((UnknownCellView *)&Map[unknown_530c])->unknown_44 = -1;
            unknown_530c = unknown_geometry_k;
        }
        return result;
    }
    return false;
}
