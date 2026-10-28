// WaypointPathClass::WaypointPathClass(NoInitClass const &noinit) (0x00724BB0): the vtables only.
#include "shared/waypoint_path.hpp"
// @ref ??0AbstractClass@@QAE@ABVNoInitClass@@@Z=0040ff60
// @ref ??_7?$DynamicVectorClass@UWaypointClass@@@@6B@=007aef8c

WaypointPathClass::WaypointPathClass(NoInitClass const &noinit) :
    AbstractClass(noinit),
    Waypoints(noinit)
{
}
