// TAction damage at006AFD80, independently755+13. Native five ordered blasts and bridge redraw.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/tactical.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ??0?$TPoint3D@H@@QAE@HHH@Z=0041b630
bool TActionClass::unknown_damage_006afd80(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    int damage = 100;
    Unknown_0047E2C0(unknown_6b2e80(), damage, 0, Rules->unknown_c74, 1);
    damage = 100;
    Unknown_0047E2C0(unknown_6b2e80() + CoordStruct(85, 85, 0), damage, 0, Rules->unknown_c74, 1);
    damage = 100;
    Unknown_0047E2C0(unknown_6b2e80() + CoordStruct(-85, 85, 0), damage, 0, Rules->unknown_c74, 1);
    damage = 100;
    Unknown_0047E2C0(unknown_6b2e80() + CoordStruct(85, -85, 0), damage, 0, Rules->unknown_c74, 1);
    damage = 100;
    Unknown_0047E2C0(unknown_6b2e80() + CoordStruct(-85, -85, 0), damage, 0, Rules->unknown_c74, 1);
    if (unknown_id_source_a3d290->Unknown_00663240(Data)) {
        Cell spot = unknown_id_source_a3d290->Get_Waypoint_Location(Data);
        int tries = 3;
        while (!Map.Unknown_00569090(&spot) && tries-- > 0) {}
        Point2D point;
        CoordStruct coord = CoordStruct(spot);
        coord.Z += unknown_geometry_j;
        unknown_tactical_83996c->Coord_To_Pixel(coord, point);
        Rect dirty(point.X - 128, point.Y - 128, 256, 256);
        unknown_tactical_83996c->Register_Dirty_Area(dirty, false);
    }
    return true;
}
