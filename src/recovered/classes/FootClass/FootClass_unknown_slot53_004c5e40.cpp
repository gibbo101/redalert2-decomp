// bool FootClass::unknown_slot53(CoordStruct const *coord, int dir) (0x004C5E40)
// Puts the unit on the map (TechnoClass's slot 53): the locomotor is
// unlimboed and powered (off for an ion-sensitive locomotor while the
// house's test 0x0051FC80 holds), the owner is told (slot 96), the eight
// neighbouring cells gain one at +0x122, the cell is recorded (or the
// tracker at 0x00839EA0 hears of a ConsideredAircraft type), the threat
// coefficient is copied and a sensor type senses around itself.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
#include "shared/house.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot53@TechnoClass@@UAE_NPBUCoordStruct@@H@Z=006c4610
// @ref ?Unknown_0051FC80@HouseClass@@QAE_NXZ=0051fc80
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// @ref ?Unknown_004131E0@UnknownTracker839EA0@@QAEXPAVFootClass@@@Z=004131e0

bool FootClass::unknown_slot53(CoordStruct const *coord, int dir)
{
    if (TechnoClass::unknown_slot53(coord, dir)) {
        Locomotor.Checked()->Unlimbo();
        if (House->Unknown_0051FC80() && Locomotor.Checked()->Is_Ion_Sensitive()) {
            Locomotor.Checked()->Power_Off();
        } else {
            Locomotor.Checked()->Power_On();
        }
        unknown_slot96(House);
        unknown_4d0 = -1;
        Cell cell = unknown_slot104();
        for (int facing = 0; facing < 8; facing++) {
            UnknownCellClass *next = (UnknownCellClass *)&Map[Adjacent_Cell(cell, facing)];
            next->unknown_122++;
        }
        if (!unknown_slot21()) {
            unknown_454 = cell;
        } else if (unknown_slot32()->ConsideredAircraft) {
            unknown_tracker_839ea0.Unknown_004131E0(this);
        }
        double threat = unknown_slot32()->ThreatAvoidanceCoefficient;
        unknown_428 = threat;
        if (unknown_slot32()->SensorsSight != 0) {
            unknown_slot285(unknown_geometry_k);
        }
        return true;
    }
    return false;
}
