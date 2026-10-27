// bool FootClass::unknown_slot52() (0x004C9BD0)
// Taking the unit off the map: the eight cells around its cell lose one
// from +0x122, the unit stops (slot 291) unless 0x00A40774 is set, the
// locomotor clears its occupation bits, the sound stops, a sensor type
// clears its sensed cell (slot 286), and the tracker at 0x00839EA0 hears of
// it when slot 178 gives a cell; then TechnoClass's slot 52.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?Unknown_00405FE0@UnknownAudioController@@QAEXXZ=00405fe0
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?Unknown_00413310@UnknownTracker839EA0@@QAEXPAVFootClass@@@Z=00413310
// @ref ?unknown_slot52@TechnoClass@@UAE_NXZ=006c4480

bool FootClass::unknown_slot52()
{
    if (!unknown_76 && unknown_slot32() != 0) {
        Cell cell = unknown_454;
        for (int facing = 0; facing < 8; facing++) {
            UnknownCellClass *next = (UnknownCellClass *)&Map[Adjacent_Cell(cell, facing)];
            next->unknown_122--;
        }
        if (unknown_a40774 == 0) {
            unknown_slot291();
        }
        if (Locomotor) {
            Locomotor.Checked()->Mark_All_Occupation_Bits(0);
        }
        unknown_43c.Unknown_00405FE0();
        if (unknown_slot32()->SensorsSight != 0) {
            unknown_slot286(unknown_geometry_k);
        }
        if (unknown_slot178() != unknown_geometry_k) {
            unknown_tracker_839ea0.Unknown_00413310(this);
        }
    }
    return TechnoClass::unknown_slot52();
}
