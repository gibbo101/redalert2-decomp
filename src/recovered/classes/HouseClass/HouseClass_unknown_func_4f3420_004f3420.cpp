// void HouseClass::unknown_func_4f3420() (0x004F3420)
// Rebuilds the house's threat map (+0x56D0): every techno on the map adds its
// threat (slot 168) to the regions around its cell; foot objects of this
// house, or of its allies when a human controls it, are left out. Called when
// an alliance changes. 0x004E5DC0 (RA's Adjust_Threat) expands in both branches.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"

void HouseClass::unknown_func_4f3420()
{
    for (int region = 0; region < 0x4204; region++) {
        unknown_56d0[region].Threat = 0;
    }
    for (int index = Technos.Count() - 1; index >= 0; index--) {
        TechnoClass *techno = Technos[index];
        if (techno->unknown_76 || !techno->unknown_7d) {
            continue;
        }
        int threat = techno->unknown_slot168();
        if (threat <= 0) {
            continue;
        }
        FootClass *foot = (techno->Kind_Of() == 15 || techno->Kind_Of() == 1 || techno->Kind_Of() == 2) ? (FootClass *)techno : 0;
        if (foot != 0) {
            if (foot->unknown_454 == unknown_cell_a40f10) {
                continue;
            }
            int region = Map.Unknown_0054E370(foot->unknown_454);
            if (foot->House == this) {
                continue;
            }
            if (Is_Human_Control() && Is_Ally(foot->House)) {
                continue;
            }
            unknown_func_4e5dc0(region, threat);
        } else {
            unknown_func_4e5dc0(Map.Unknown_0054E370(((CellClass *)techno->unknown_slot105())->MapCoords), threat);
        }
    }
}
