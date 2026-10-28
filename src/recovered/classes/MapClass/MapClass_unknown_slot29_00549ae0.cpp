// void MapClass::unknown_slot29(Rect const &rect) (0x00549AE0, slot 29)
// Sets the local map rectangle (+0xF8) to the part of rect inside MapSize,
// at least 2 in from the left and top and 2 / 6 cells clear of the right
// and bottom edges, flags a full redraw, and refreshes every techno's +0x32D
// cell test (0x0055A660); a techno that just passed it, whose house answers
// 0x004F52B0, of a kind other than 6, with +0x7D set and +0x76 clear, gets
// its slot 70 (false, false).
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/house_screen.hpp"
#include "shared/map_view.hpp"
#include "shared/map_techno.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ?unknown_list_a40c20@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20

void MapClass::unknown_slot29(Rect const &rect)
{
    MapLocalSize = Intersect(rect, MapSize);
    MapLocalSize.X = MapLocalSize.X > 2 ? MapLocalSize.X : 2;
    MapLocalSize.Y = MapLocalSize.Y > 2 ? MapLocalSize.Y : 2;
    MapLocalSize.Width = MapLocalSize.Width < MapSize.Width - MapLocalSize.X - 2 ? MapLocalSize.Width : MapSize.Width - MapLocalSize.X - 2;
    MapLocalSize.Height = MapLocalSize.Height < MapSize.Height - MapLocalSize.Y - 6 ? MapLocalSize.Height : MapSize.Height - MapLocalSize.Y - 6;
    Map.Flag_To_Redraw(2);
    for (int index = 0; index < unknown_list_a40c20.Count(); index++) {
        TechnoClass *techno = unknown_list_a40c20[index];
        bool was = techno->unknown_32d;
        techno->unknown_32d = Unknown_0055A660(techno->unknown_slot104(), true);
        if (!was && techno->unknown_32d && techno->House->Unknown_004F52B0()
            && techno->Kind_Of() != 6 && techno->unknown_7d && !techno->unknown_76) {
            techno->unknown_slot70(false, false);
        }
    }
}
