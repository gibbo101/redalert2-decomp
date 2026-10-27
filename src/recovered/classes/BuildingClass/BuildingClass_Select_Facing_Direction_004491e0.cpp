// Round the current facing to an image frame direction, or face the target.
#include "shared/building.hpp"
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0
UnknownFacingDir BuildingClass::unknown_slot183()
{
    if(!unknown_228)
        return (unsigned short)(Dir_To_256(unknown_2e0.Current())<<8);
    if(unknown_slot232() && !Type->TurretAnimIsVoxel)
        return (unsigned short)(Dir_To_32(unknown_2e0.Current())*2048);
    return unknown_slot285(unknown_228);
}
