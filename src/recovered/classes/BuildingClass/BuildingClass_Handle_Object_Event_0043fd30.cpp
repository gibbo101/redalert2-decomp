// Handle a building object action and queue the corresponding packed network event.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ??0EventClass@@QAE@HHVTargetClass@@@Z=004b5ef0
// @ref ??0EventClass@@QAE@HHVTargetClass@@0@Z=004b6090
// @ref ?OutList@@3V?$QueueClass@VEventClass@@$0IA@@@A=00a32338
// @ref __imp__timeGetTime@0=0079a524
// @ref ?unknown_440140@BuildingClass@@QAEXPBVCell@@_N@Z=00440140
bool BuildingClass::unknown_slot78(int action,int target_address,bool arg3)
{
    ObjectClass *target=(ObjectClass *)target_address;
    if(action==5) {
        if(target) unknown_slot200(1,target,0,0);
    } else if(action==4) {
        if(Type->Factory!=0) OutList.Add(EventClass(Owner(),0x11,TargetClass(this)));
        if(Type->GapGenerator) unknown_slot200(0x10,target,0,0);
        if(unknown_554.Count()>0) {
            unknown_slot200(0x10,target,0,0);
            return true;
        }
    } else {
        if(action==0x37) {
            return (OutList.Add(EventClass(unknown_38->unknown_28->ArrayIndex,10,TargetClass(this))),true);
        } else {
            if(action!=1) return true;
            int factory=Type->Factory;
            if(factory==16 || factory==40 || factory==3) {
                Cell cell=Coord_Cell(target->Center_Coord());
                unknown_440140(&cell,true);
                return true;
            }
            return (OutList.Add(EventClass(Owner(),0x1e,TargetClass(this),TargetClass(target))),true);
        }
    }
    return true;
}
