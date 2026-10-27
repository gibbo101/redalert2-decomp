// Object cell level plus bridge offset; existing const interface is a hypothesis.
#include "shared/object.hpp"
#include "shared/cell.hpp"
int ObjectClass::Unknown_005D47D0() const
{
    CellClass *cell = static_cast<CellClass *>(const_cast<ObjectClass *>(this)->unknown_slot105());
    return cell->unknown_11b + (unknown_79 ? 4 : 0);
}
