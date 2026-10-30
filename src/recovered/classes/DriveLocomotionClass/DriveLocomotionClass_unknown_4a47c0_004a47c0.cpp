// bool DriveLocomotionClass::unknown_4a47c0(Cell cell) (0x004A47C0)
// Whether the unit may enter the cell (MapClass 0x0055ACD0). Unreferenced.
#include "shared/drive_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_0055ACD0@MapClass@@QAE_NPAVObjectClass@@ABVCell@@@Z=0055acd0

bool DriveLocomotionClass::unknown_4a47c0(Cell cell)
{
    return Map.Unknown_0055ACD0(LinkedTo, cell);
}
