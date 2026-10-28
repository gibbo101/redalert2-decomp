// void FoggedObjectClass::unknown_4c1ae0() (0x004C1AE0)
// Marks (+0x140 bit 22) the cell of every listed fogged object: each cell a fogged
// building covers (its cell plus the type's cell offsets), or the cell under the coordinate.
#include "shared/fogged_object.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/object_type.hpp"

void FoggedObjectClass::unknown_4c1ae0()
{
    for (int index = 0; index < Array.Count(); index++) {
        FoggedObjectClass *fogged = Array[index];
        if (fogged->unknown_4c1f00() != 0) {
            Cell const *offset = fogged->unknown_4c1f00();
            Cell base = fogged->unknown_slot24();
            for (; offset->X != 0x7FFF || offset->Y != 0x7FFF; offset++) {
                Cell cell = Cell(offset->X + base.X, offset->Y + base.Y);
                Map[cell].unknown_140 |= 0x400000;
            }
        } else {
            CoordStruct coord = fogged->Coord;
            Map[coord].unknown_140 |= 0x400000;
        }
    }
}
