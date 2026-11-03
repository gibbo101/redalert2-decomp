// Applies Iron Curtain to occupants around the waypoint and starts its invocation animation.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
extern int const unknown_cell_count_7a590c;
extern Cell const unknown_cell_offsets_a6f248[];
// @ref ?unknown_cell_count_7a590c@@3HB=007a590c
// @ref ?unknown_cell_offsets_a6f248@@3QBVCell@@B=00a6f248
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180

bool TActionClass::unknown_iron_curtain_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell target_cell;
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct position = Map[waypoint].Center_Coord();
    new AnimClass(Rules->IronCurtainInvokeAnim, position + CoordStruct(0,0,5), 0,1,0x600,0);
    int count = unknown_cell_count_7a590c;
    for (int index = 0; index < count; ++index) {
        Cell const &offset = unknown_cell_offsets_a6f248[index];
        target_cell = TPoint2D<short>((short)(waypoint.X + offset.X), (short)(waypoint.Y + offset.Y));
        CellClass &target = Map[target_cell];
        ObjectClass *occupier = target.OccupierPtr;
        while (occupier != 0) {
            occupier->unknown_slot82(Rules->IronCurtainDuration);
            occupier = occupier->unknown_30;
        }
    }
    return true;
}
