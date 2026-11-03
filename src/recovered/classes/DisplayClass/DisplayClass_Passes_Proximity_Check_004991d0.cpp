// bool DisplayClass::Passes_Proximity_Check_004991D0(ObjectTypeClass const *object, int house, Cell const *list, Cell const &trycell) const (0x004991D0)
// TibSun DisplayClass::Passes_Proximity_Check: whether a building placed at trycell touches one of the
// house's base buildings (or, with the session's ally-building option, an allied eligible one). The
// foundation is a Rect built from the two size calls as constructor arguments (as Passes_Shroud_Check);
// the loops test against xmin + xsize and ymin + ysize, which VC6 hoists into the loop preheaders.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/session_state.hpp"
#include "shared/rect.hpp"
// @ref ?unknown_cell_852610@@3VCell@@A=00852610
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?unknown_a40d13@@3_NA=00a40d13
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940

bool DisplayClass::Passes_Proximity_Check_004991D0(ObjectTypeClass const *object, int house, Cell const *list, Cell const &trycell) const
{
    if (house != unknown_player_a35db4->ArrayIndex) {
        return true;
    }

    if (unknown_a40d13) {
        return true;
    }

    if (list == 0 || trycell == unknown_cell_852610) {
        return true;
    }

    if (object == 0 || object->Kind_Of() != 7) {
        return true;
    }

    BuildingTypeClass const *building = (BuildingTypeClass const *)object;

    Rect rect(trycell.X, trycell.Y, building->Width(), building->Foundation_Height(false));

    int adj = (building->Adjacent + 1);

    int xmin = rect.X - adj;
    int ymin = rect.Y - adj;

    int xsize = (2 * adj) + rect.Width;
    int ysize = (2 * adj) + rect.Height;

    bool retval = false;

    for (int x = xmin; x < xmin + xsize; x++) {
        for (int y = ymin; y < ymin + ysize; y++) {
            Cell newcell(x, y);

            if (!rect.Is_Point_Within(Point2D(newcell.X, newcell.Y))) {
                CellClass *cellptr = &Map[newcell];

                BuildingClass *newbase = (BuildingClass *)cellptr->unknown_4717b0();

                if (newbase != 0) {
                    if (newbase->House->ArrayIndex == house && newbase->Type->BaseNormal) {
                        retval = true;
                    }
                    if (unknown_session_a3d298.unknown_2c && newbase->House->Is_Ally(Houses[house]) && newbase->Type->EligibileForAllyBuilding) {
                        retval = true;
                    }
                }
            }
        }
    }

    return retval;
}
