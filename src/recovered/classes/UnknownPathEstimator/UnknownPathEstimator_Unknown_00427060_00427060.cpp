// UnknownPathEstimator::Unknown_00427060() (0x00427060): the cell at the end
// of count steps along a list of facings.
#ifndef VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#endif
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/path_estimator.hpp"
#include "shared/cell.hpp"
#include "shared/subzone_tracking.hpp"
#include "shared/map_view.hpp"
#include "shared/tube.hpp"
// @ref ?unknown_path_facing_table_7cf100@@3PAY02HA=007cf100
// @ref ?unknown_path_facing_offsets_84c838@@3PAHA=0084c838

// The unit expands its DynamicVectorClass constructors and calls the VectorClass base constructors
// (0x0042B510, 0x0042B620) out of line.
template <>
inline DynamicVectorClass<unsigned int>::DynamicVectorClass(unsigned size, unsigned int const *array)
    : VectorClass<unsigned int>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
template <>
inline DynamicVectorClass<unsigned short>::DynamicVectorClass(unsigned size, unsigned short const *array)
    : VectorClass<unsigned short>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}

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
