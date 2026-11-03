// bool DisplayClass::Unknown_00499390(BuildingTypeClass *type, int house, int arg3, Cell const *cell) (0x00499390)
// TibSun DisplayClass::Passes_Shroud_Check: whether a building placed at cell avoids the shroud. Always true
// for another house than the player's, with 0x00A40D13 set, without a cell list (arg3), at the null cell or
// for anything but a building type. Otherwise a shrouded foundation cell fails unless the type's +0xBF0
// (TibSun ToTile) is set. The foundation is a Rect built from the two size calls as constructor arguments
// (Foundation_Height is called first; only Y spills, to the Rect's own slot).
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/rect.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Unknown_0055A280@MapClass@@QAEHABUCoordStruct@@@Z=0055a280
// @ref ?Unknown_00568140@MapClass@@QAE_NABUCoordStruct@@@Z=00568140

bool DisplayClass::Unknown_00499390(BuildingTypeClass *type, int house, int arg3, Cell const *cell)
{
    if (house != unknown_player_a35db4->ArrayIndex) {
        return true;
    }
    if (unknown_a40d13) {
        return true;
    }
    if (arg3 == 0 || *cell == unknown_geometry_k) {
        return true;
    }
    if (type == 0 || type->Kind_Of() != 7) {
        return true;
    }

    Rect rect(cell->X, cell->Y, type->Width(), type->Foundation_Height(false));

    bool shrouded = false;
    for (int x = rect.X; x < rect.X + rect.Width; x++) {
        for (int y = rect.Y; y < rect.Y + rect.Height; y++) {
            CoordStruct coord = Cell_Coord(XY_Cell(x, y));
            coord.Z = Map.Unknown_0055A280(coord);
            if (Map.Unknown_00568140(coord)) {
                shrouded = true;
                break;
            }
        }
        if (shrouded) {
            if (type->unknown_bf0 == 0) {
                return false;
            }
            break;
        }
    }
    return true;
}
