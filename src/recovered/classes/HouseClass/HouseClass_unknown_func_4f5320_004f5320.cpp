// bool HouseClass::unknown_func_4f5320(BuildingTypeClass *type, Cell const &cell) (0x004F5320)
// Outside the campaign: whether any cell of the type's foundation at the cell,
// widened by Rules AIBaseSpacing on every side, has this house's bit in its
// +0xDC house mask. The campaign always answers true.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

bool HouseClass::unknown_func_4f5320(BuildingTypeClass *type, Cell const &cell)
{
    if (unknown_game_mode_a3d298 == 0) {
        return true;
    }
    int spacing = Rules->AIBaseSpacing;
    int width = type->Width() + spacing * 2;
    int height = type->Foundation_Height(false) + spacing * 2;
    int bit = 1 << ArrayIndex;
    for (int x = cell.X - spacing - 1; x < cell.X + width + 1; x++) {
        for (int y = cell.Y - spacing - 1; y < cell.Y + height + 1; y++) {
            if (Map[Cell(x, y)].unknown_dc & bit) {
                return true;
            }
        }
    }
    return false;
}
