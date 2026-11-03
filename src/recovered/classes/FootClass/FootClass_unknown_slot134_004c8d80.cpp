// int FootClass::unknown_slot134() (0x004C8D80)
// A two-state retreat: with no destination the unit heads for a cell on
// its house's map edge (0x0049A700), near the team's waypoint when it has
// one, and switches to state 1; state 1 falls back to 0 once it arrives.
// Returns the mission's rate in frames plus 0..2.
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049A700@DisplayClass@@QAE?AVCell@@HABV2@0H_NH@Z=0049a700
// @ref ?Unknown_006BFA90@TeamTypeClass@@QBE?AVCell@@XZ=006bfa90
// @ref ?Control@MissionClass@@QBEPAVMissionControlClass@@XZ=005950d0
// @ref __real@8@4008e100000000000000=0079b608
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290

int FootClass::unknown_slot134()
{
    switch (unknown_a8) {
    case 0:
        if (unknown_494 != 0) {
            unknown_a8 = 1;
        } else {
            Cell cell(0, 0);
            if (Team != 0 && Team->Class->Unknown_006BFA90() != unknown_geometry_k) {
                cell = Map.Unknown_0049A700(House->unknown_128, Team->Class->Unknown_006BFA90(),
                    Coord_Cell(Center_Coord()), unknown_slot32()->SpeedType, 1, 0);
            }
            if (cell == unknown_geometry_k) {
                cell = Map.Unknown_0049A700(House->unknown_128, unknown_geometry_k,
                    Coord_Cell(Center_Coord()), unknown_slot32()->SpeedType, 1, 0);
            }
            unknown_slot260((AbstractClass *)&Map[cell], 1);
            unknown_a8 = 1;
        }
        break;
    case 1:
        if (unknown_494 == 0) {
            unknown_a8 = 0;
        }
        break;
    }
    int delay = (int)(Control()->unknown_10 * 900.0);
    return delay + unknown_id_source_a3d290->Random()(0, 2);
}
