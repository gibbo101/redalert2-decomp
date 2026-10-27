// void BuildingClass::unknown_44da20(InfantryClass *infantry) (0x0044DA20)
// Removes the infantry from unknown_53c and adds it at the end again.
#define VECTOR_IMPLEMENT_ALL
#include "shared/building.hpp"

void BuildingClass::unknown_44da20(InfantryClass *infantry)
{
    unknown_53c.Delete(infantry);
    unknown_53c.Add(infantry);
}
