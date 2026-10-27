// void ObjectClass::unknown_slot57() (0x005D2AC0, slot 57)
// Sets +0x7A and +0x7C, takes the object off the map's lists (slot 71 (0),
// 0x00499A90), clears +0x79 and puts it back (0x00499A40, slot 71 (1)).
// A foot then re-marks its cell: through slot 59 at its coordinate when its
// locomotor is not moving, else the locomotor clears its occupation bits.
#include "shared/object_type.hpp"
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940

void ObjectClass::unknown_slot57()
{
    unknown_7a = true;
    unknown_7c = true;
    unknown_slot71(0);
    Map.Remove(this);
    unknown_79 = false;
    Map.Submit(this);
    unknown_slot71(1);
    bool foot;
    if (this != 0) {
        foot = unknown_14_bit2;
    }
    if (this != 0 && foot) {
        if (!((FootClass *)this)->Locomotor.Checked()->Is_Moving()) {
            CoordStruct coord = Coord;
            unknown_slot59(coord);
            return;
        }
        ((FootClass *)this)->Locomotor.Checked()->Mark_All_Occupation_Bits(0);
    }
}
