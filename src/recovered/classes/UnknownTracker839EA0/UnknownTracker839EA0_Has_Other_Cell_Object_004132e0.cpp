// Whether another object occupies the cell beneath this foot.
#include "shared/foot.hpp"
#include "shared/cell.hpp"
bool UnknownTracker839EA0::Unknown_004132E0(FootClass *foot)
{
    void *occupant=static_cast<CellClass *>(foot->unknown_slot105())->unknown_e0;
    if (occupant && occupant!=foot) return true;
    return false;
}
