// bool TActionClass::unknown_func_6b14d0(...) (0x006B14D0)
// Kills every living, active techno whose tag has the trigger attached (repeating while any was hit), then scrolls the tactical view to the cell unless it is the unset cell; true when any was killed.
#include "shared/taction.hpp"
#include "shared/techno.hpp"
#include "shared/tag.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
// @ref ?Unknown_00569090@MapClass@@QAE_NPAVCell@@@Z=00569090
// @ref ?unknown_cell_abfdb0@@3VCell@@A=00abfdb0
extern Cell unknown_cell_abfdb0;   // 0x00ABFDB0

bool TActionClass::unknown_func_6b14d0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool killed = false;
    bool again;
    do {
        again = false;
        for (int index = 0; index < Technos.Count(); index++) {
            TechnoClass *techno = Technos[index];
            if (techno->Strength > 0 && techno->unknown_7d && techno->unknown_74 && !techno->unknown_76 && techno->unknown_34 != 0
                && techno->unknown_34->Is_Trigger_Attached(trigger)) {
                int damage = techno->Strength;
                techno->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 0);
                killed = true;
                again = true;
                index--;
            }
        }
    } while (again);
    if (cell->X != unknown_cell_abfdb0.X || cell->Y != unknown_cell_abfdb0.Y) {
        bool visible = Map.Unknown_00569090(cell);
        int tries = 3;
        while (!visible && tries-- > 0) {
            visible = Map.Unknown_00569090(cell);
        }
        CoordStruct coord = CoordStruct(cell->X * 256 + 128, cell->Y * 256 + 128, 0);
        coord.Z = unknown_geometry_j;
        Point2D pixel;
        unknown_tactical_83996c->Unknown_006A29D0(coord, pixel);
        unknown_tactical_83996c->Unknown_006A3020(Rect(pixel.X - 0x80, pixel.Y - 0x80, 0x100, 0x100), 0);
    }
    return killed;
}
