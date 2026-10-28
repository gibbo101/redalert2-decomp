// void CaptureManagerClass::Draw_Link() (0x00468150)
// Draws the control link from the owner (slot 43 coordinate) to the
// controlled techno (70 leptons above it) in the owner house's colour
// (TechnoClass 0x006D0990).
#include "shared/capture_manager.hpp"
#include "shared/techno.hpp"
// @ref ?unknown_6d0990@TechnoClass@@QAEXUCoordStruct@@0VRGBClass@@@Z=006d0990

void CaptureManagerClass::Draw_Link()
{
    if (Owner != 0 && unknown_24 != 0) {
        CoordStruct to = unknown_24->Coord;
        to.Z += 70;
        Owner->unknown_6d0990(Owner->unknown_slot43(0), to, Owner->House->unknown_55e9);
    }
}
