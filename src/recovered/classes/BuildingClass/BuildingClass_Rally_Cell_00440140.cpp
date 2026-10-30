// 00440140: select a reachable rally cell and queue the building's target event.
// Full original body is 777 bytes, including both queue-add paths, plus 7 NOPs.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/house.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
#include "shared/vox_class.hpp"
extern char const unknown_rally_speech_007cf810[];
// @ref ?unknown_rally_speech_007cf810@@=007cf810
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ??0EventClass@@QAE@HHVTargetClass@@0@Z=004b6090
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524
void BuildingClass::unknown_440140(Cell const *cell, bool announce)
{
    int speed = 0;
    int zone_type = 0;
    bool bridge = ((Map[*cell].unknown_140 >> 8) & 1) != 0;
    if (Type->Factory == 3) { speed = 4; zone_type = 9; }
    if (Type->Naval) { speed = 6; zone_type = 4; }
    CoordStruct location=Coord;
    int zone = Map.Zone(Coord_Cell(location), zone_type, bridge);
    Cell found = Map.Unknown_005502E0(*cell, speed, zone, zone_type, bridge, Point2D(1,1), 0,0,0,1,Cell(0,0),0);
    if (found != *(Cell const *)&unknown_84ed10) {
        OutList.Add(EventClass(Owner(),0x1e,TargetClass(this),TargetClass((AbstractClass *)&Map[found])));
    } else if (Type->ConstructionYard && House->Unknown_004F52F0() && unknown_game_mode_a3d298 && unknown_flag_a3d340) {
        OutList.Add(EventClass(Owner(),0x1e,TargetClass(this),TargetClass((AbstractClass *)&Map[Center_Coord()])));
        return;
    }
    if (announce && House->Unknown_004F52B0() && !Type->ConstructionYard) {
        Speech_Play_Name(unknown_rally_speech_007cf810,-1,-1);
    }
}
