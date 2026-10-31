// Find a nearby reachable cell using this object's speed and movement zone.
#include "shared/techno.hpp"
#include "shared/map_view.hpp"
Cell TechnoClass::unknown_6cf130(AbstractClass *target)
{
    int speed=unknown_slot32()->SpeedType;
    if(speed==4) speed=1;
    Cell cell;
    if(target) cell=Cell(target->Center_Coord());
    else cell=Cell(Center_Coord());
    int movement_zone=unknown_slot32()->MovementZone;
    int zone=movement_zone!=-1 ? Map.Zone(cell,movement_zone,unknown_79) : -1;
    return Map.Unknown_005502E0(cell,speed,zone,movement_zone,unknown_79,Point2D(1,1),0,0,0,1,Cell(0,0),0);
}
