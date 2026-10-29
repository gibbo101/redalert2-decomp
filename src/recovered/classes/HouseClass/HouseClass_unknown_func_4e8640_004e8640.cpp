// void HouseClass::unknown_func_4e8640() (0x004E8640)
// RA's Recalc_Center: the base centre is the cost-weighted average position
// of the house's live buildings, moved to the centre of a reachable cell
// near it; the radius their mean distance from it (at least 0x200); each
// zone's defence the sum of its buildings' anti-air, anti-armour and
// anti-infantry strengths.
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
#include "shared/building_type_class.hpp"
#include "shared/map_view.hpp"
#include "shared/coord_distance.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@HHHH0H@Z=005502e0

// The distance between two coordinates (as shared/coord_distance.hpp's
// Coord_Distance, with the last two squares summed first).
inline int Base_Distance(CoordStruct const &a, CoordStruct const &b)
{
    CoordStruct d(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    return (int)unknown_sqrt_4ba410((double)d.X * d.X + ((double)d.Z * d.Z + (double)d.Y * d.Y));
}

void HouseClass::unknown_func_4e8640()
{
    BaseCenter = unknown_geometry_l;
    unknown_53c8 = 0;
    for (int zone = 0; zone < 5; zone++) {
        ZoneInfo[zone].AirDefense = 0;
        ZoneInfo[zone].ArmorDefense = 0;
        ZoneInfo[zone].InfantryDefense = 0;
    }
    if (CurBuildings > 0) {
        int x = 0;
        int y = 0;
        int count = 0;
        int buildings = Buildings.Count();
        for (int index = 0; index < buildings; index++) {
            UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
            if (building != 0 && !building->unknown_76 && building->Strength > 0) {
                int weight = building->Type->unknown_slot33((int)this) / 1000 + 1;
                for (int i = 0; i < weight; i++) {
                    x += building->Center_Coord().X;
                    y += building->Center_Coord().Y;
                    count++;
                }
            }
        }
        if (count > 0) {
            x /= count;
            y /= count;
            BaseCenter = CoordStruct(x, y, 0);
            BaseCenter = Cell_Coord(Map.Unknown_005502E0(Coord_Cell(BaseCenter), 0, -1, 0, false, Point2D(1, 1), 0, 0, 0, 1, Cell(0, 0), 0));
        }
        if (count > 1) {
            int radius = 0;
            int buildings = Buildings.Count();
            for (int index = 0; index < buildings; index++) {
                UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
                if (building != 0 && !building->unknown_76 && building->Strength > 0) {
                    radius += Base_Distance(BaseCenter, building->Center_Coord());
                }
            }
            radius /= count;
            if (radius <= 0x200) {
                radius = 0x200;
            }
            unknown_53c8 = radius;
            buildings = Buildings.Count();
            for (index = 0; index < buildings; index++) {
                UnknownBuildingView *building = (UnknownBuildingView *)Buildings[index];
                if (building != 0 && !building->unknown_76 && building->Strength > 0) {
                    int zone = Which_Zone(building->Center_Coord());
                    if (zone != -1) {
                        ZoneInfo[zone].ArmorDefense += building->unknown_6d5900();
                        ZoneInfo[zone].AirDefense += building->unknown_6d5870();
                        ZoneInfo[zone].InfantryDefense += building->unknown_6d59d0();
                    }
                }
            }
        } else {
            unknown_53c8 = 0x200;
        }
    }
}
