// bool DriveLocomotionClass::Start_Driver(CoordStruct const &headto) (0x004A0EE0)
// Heads for a coordinate: taken (and its track marked) when the object may
// stand in its cell; otherwise dropped again when +0x7D is set (Westwood's
// DriveClass::Start_Driver). Expanded where it is used; this out-of-line
// copy is never called.
#include "shared/drive_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_coord_852998@@3UCoordStruct@@A=00852998
// @ref ?unknown_476cc0@CellClass@@QAE_NPAVObjectClass@@@Z=00476cc0

bool DriveLocomotionClass::Start_Driver(CoordStruct const &headto)
{
    Stop_Driver();
    if (headto != unknown_coord_852998) {
        unknown_40 = headto;
        unknown_63 = true;
        if (Map[headto].unknown_476cc0(LinkedTo) && !LinkedTo->unknown_76) {
            unknown_4a0bc0(headto, 1);
            return true;
        }
        if (LinkedTo->unknown_7d) {
            unknown_40 = unknown_coord_852998;
            unknown_63 = false;
        }
    }
    return false;
}
