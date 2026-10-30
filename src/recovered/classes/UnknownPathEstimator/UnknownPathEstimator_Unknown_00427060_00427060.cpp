// UnknownPathEstimator::Unknown_00427060() (0x00427060): the cell at the end
// of count steps along a list of facings.
#ifndef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#ifndef VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#define VECTOR_IMPLEMENT_DYNAMIC_CONSTRUCTOR
#endif
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/path_estimator.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/tube.hpp"
// @ref ?unknown_path_facing_table_7cf100@@3PAY02HA=007cf100
// @ref ?unknown_path_facing_offsets_84c838@@3PAHA=0084c838

// The unit's out-of-line copy is the COMDAT 0x0042AD50 (0x00428CF0 calls it).
inline Cell __fastcall UnknownPathEstimator::Unknown_0042AD50(Cell const &cell, int facing)
{
    if (facing == 8) {
        int tube = Map[cell].unknown_116;
        if (tube != -1) {
            return unknown_TubeClass_list_008661c8[tube]->ExitCell;
        }
        return Cell(0, 0);
    }
    return cell + AdjacentCell[facing];
}

Cell __fastcall UnknownPathEstimator::Unknown_00427060(Cell const &start, int count, int const *facings)
{
    Cell cell = start;
    for (int index = 0; index < count; index++) {
        cell = Unknown_0042AD50(cell, facings[index]);
    }
    return cell;
}
