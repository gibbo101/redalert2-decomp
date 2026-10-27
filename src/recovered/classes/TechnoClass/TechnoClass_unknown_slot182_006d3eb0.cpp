// int TechnoClass::unknown_slot182(AbstractClass *object, Cell *cell) (0x006D3EB0, slot 182)
// Stores the zero cell; returns 0.
#include "shared/techno.hpp"
// @ref _unknown_geometry_k=00ac0148

int TechnoClass::unknown_slot182(AbstractClass *object, Cell *cell)
{
    *cell = unknown_geometry_k;
    return 0;
}
