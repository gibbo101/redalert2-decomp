#include "shared/coord.hpp"
// Five ordered three-int coordinate records, at a twelve-byte stride.
// @ref ?unknown_cell_offsets_00850e50@@=00850e50
extern CoordStruct unknown_cell_offsets_00850e50[5];
void Initialize_Cell_Offsets_00483390()
{
    unknown_cell_offsets_00850e50[0] = CoordStruct(128,128,0);
    unknown_cell_offsets_00850e50[1] = CoordStruct(64,64,0);
    unknown_cell_offsets_00850e50[2] = CoordStruct(192,64,0);
    unknown_cell_offsets_00850e50[3] = CoordStruct(64,192,0);
    unknown_cell_offsets_00850e50[4] = CoordStruct(192,192,0);
}
