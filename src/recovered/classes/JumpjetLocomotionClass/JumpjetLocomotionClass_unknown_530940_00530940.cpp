// void JumpjetLocomotionClass::unknown_530940() (0x00530940)
// Process state 5 (crashing): the object sinks by JumpjetCrash and turns
// (+0x2D00 a step); on the map it is moved to the new coordinate. Once on
// the ground (slot 108 at most 0) its cell claim is released, the arrival
// tracker is told, the speed (+0x70) cleared, the state set to 6 and the
// object notified (0x117C).
#include "shared/jumpjet_locomotion.hpp"
#include "shared/cell.hpp"
// @ref ?Unknown_00413310@UnknownTracker839EA0@@QAEXPAVTechnoClass@@@Z=00413310
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0

void JumpjetLocomotionClass::unknown_530940()
{
    CoordStruct coord = LinkedTo->Coord;
    coord.Z -= Crash;
    {
        UnknownFacingDir dir = UnknownFacingDir((unsigned short)(unknown_50.Current().Raw + 0x2D00));
        unknown_50.Set_Desired(dir);
    }
    Map.Unknown_0055A280(coord);
    Map[coord];
    if (Map.Unknown_0054AAB0(Coord_Cell(coord))) {
        Map.Remove(LinkedTo);
        LinkedTo->unknown_slot71(0);
        LinkedTo->unknown_slot103(coord);
        LinkedTo->unknown_slot71(1);
        Map.Submit(LinkedTo);
    }
    if (LinkedTo->unknown_slot108() <= 0) {
        if (((CellClass *)LinkedTo->unknown_slot105())->unknown_e0 == LinkedTo) {
            ((CellClass *)LinkedTo->unknown_slot105())->Set_unknown_e0(0);
        }
        unknown_tracker_839ea0.Unknown_00413310(LinkedTo);
        unknown_4c = 6;
        unknown_70 = 0;
        LinkedTo->INoticeSink_Unknown(0x117C, 0);
    }
}
