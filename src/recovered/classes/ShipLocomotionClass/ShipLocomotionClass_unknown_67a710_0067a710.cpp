// bool ShipLocomotionClass::unknown_67a710(Cell cell) (0x0067A710)
// Whether the unit may enter the cell (MapClass 0x0055ACD0). Unreferenced.
#include "shared/ship_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_0055ACD0@MapClass@@QAE_NPAVObjectClass@@ABVCell@@@Z=0055acd0

bool ShipLocomotionClass::unknown_67a710(Cell cell)
{
    return Map.Unknown_0055ACD0(LinkedTo, cell);
}
