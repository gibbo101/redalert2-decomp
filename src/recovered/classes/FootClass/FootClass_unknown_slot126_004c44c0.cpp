// int FootClass::unknown_slot126() (0x004C44C0)
// A guard step: a HoverAttack type without a value from slot 108 heads for
// a cell near itself (0x006CF130); a pending scan (+0x57E) picks a target
// (slot 219) and assigns it (slot 220); then slot 304 when there is a
// target, else slot 261. Returns the mission's rate in frames plus 0..2.
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_6cf130@TechnoClass@@QAE?AVCell@@PAVAbstractClass@@@Z=006cf130
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot126()
{
    if (unknown_slot32()->HoverAttack && unknown_slot108() == 0) {
        unknown_slot260((AbstractClass *)&Map[unknown_6cf130(this)], true);
    }
    if (unknown_57e) {
        CoordStruct coord = Coord;
        AbstractClass *target = unknown_slot219(1, &coord, 0);
        if (target != 0) {
            unknown_slot220(target);
            unknown_57e = false;
        }
    }
    if (unknown_228 != 0) {
        unknown_slot304();
    } else {
        unknown_slot261(0, true);
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
