// DynamicVectorClass<Cell> __fastcall Multiplayer_Start_Waypoints_0065fff0(bool official) (0x0065FFF0)
// The multiplayer start cells: the set waypoints among the first ones (one per
// player and computer house, or as many consecutive ones as are set), then
// random reachable cells inside the map until there are enough (Westwood's
// Build_Start_Waypoint_List; the official flag is not read).
// @ref ??_C@_0DA@BAOM@Multiplayer?5start?5waypoint?5found@=007f2294
// @ref ??_C@_0DH@HKLA@Random?5multiplayer?5start?5waypoin@=007f2210
// @ref ??_C@_0EK@OKJJ@Multiplayer?5start?5waypoint?5defic@=007f2248
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_G?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??_E?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ?Resize@?$DynamicVectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042d050
// @ref ?Clear@?$DynamicVectorClass@VCell@@@@UAEXXZ=0042cc10
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHABVCell@@@Z=0042d120
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHPBVCell@@@Z=0042cc40
// @ref ??4?$VectorClass@VCell@@@@QAEAAV0@ABV0@@Z=00663590
// @ref ?Unknown_005502E0@MapClass@@QAE?AVCell@@ABV2@HHH_NUPoint2D@@11110H@Z=005502e0
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/map_view.hpp"
#include "shared/debug_printf.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/random.hpp"

DynamicVectorClass<Cell> __fastcall Multiplayer_Start_Waypoints_0065fff0(bool official)
{
    DynamicVectorClass<Cell> waypts;

    int num_waypts = 0;
    for (int i = 0; i < 8; i++) {
        if (unknown_id_source_a3d290->Unknown_00663240(i)) {
            num_waypts++;
        } else {
            break;
        }
    }
    int observers = 0;
    for (int player = 0; player < unknown_players_a3fa7c.Count(); player++) {
        if (unknown_players_a3fa7c[player]->Team == -1) {
            observers++;
        }
    }
    // Westwood's MAX macro: the house count expression is written twice.
    int look_for = num_waypts > unknown_players_a3fa7c.Count() - observers + unknown_session_a3d298.AICount
        ? num_waypts : unknown_players_a3fa7c.Count() - observers + unknown_session_a3d298.AICount;

    for (int waycount = 0; waycount < look_for; waycount++) {
        if (unknown_id_source_a3d290->Unknown_00663240(waycount)) {
            waypts.Add(unknown_id_source_a3d290->Get_Waypoint_Location(waycount));
            Debug_Printf("Multiplayer start waypoint found at cell %d,%d\n", unknown_id_source_a3d290->Get_Waypoint_Location(waycount).X, unknown_id_source_a3d290->Get_Waypoint_Location(waycount).Y);
        }
    }

    int deficiency = look_for - waypts.Count();
    if (deficiency > 0) {
        Debug_Printf("Multiplayer start waypoint deficiency - looking for more start positions\n");
        while (waypts.Count() < look_for) {
            Cell trycell = Cell(Map.unknown_120 + Random_Pick(10, Map.unknown_128 - 10), Map.unknown_124 + 10 + Random_Pick(0, Map.unknown_12c - 10));
            trycell = Map.Unknown_005502E0(trycell, 1, -1, 0, false, Point2D(8, 8), 0, 0, 0, 1, Cell(0, 0), 0);
            if (trycell != unknown_geometry_k) {
                waypts.Add(trycell);
                Debug_Printf("Random multiplayer start waypoint added at cell %d,%d\n", trycell.X, trycell.Y);
            }
        }
    }
    return waypts;
}
