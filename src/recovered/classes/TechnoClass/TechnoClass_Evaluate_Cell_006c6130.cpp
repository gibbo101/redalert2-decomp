// Evaluate the objects occupying a cell, retaining the last eligible techno.
// Existing seven-argument ABI retained; +418 type and cell views use shared layouts.
#include "shared/techno.hpp"
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_6c5570@TechnoClass@@QAE_NHHHPAVObjectClass@@PAHHPBUCoordStruct@@@Z=006c5570
bool TechnoClass::unknown_6c6130(int method,int mask,Cell const *cell,int range,ObjectClass **object,int *value,int zone)
{
    *object=0;
    *value=0;
    UnknownCellClass *cellptr=reinterpret_cast<UnknownCellClass *>(&Map[*cell]);
    if(zone!=-1 && Map.Zone(*cell,unknown_slot32()->MovementZone,true)!=zone) return false;
    ObjectClass *tentative=cellptr->unknown_e8;
    TechnoClass *tech=0;
    if(!tentative) tentative=cellptr->unknown_e4;
    while(tentative) {
        if(tentative!=this) {
            if(!tentative) tech=0;
            else {
                if(tentative->unknown_14_bit0) tech=static_cast<TechnoClass *>(tentative);
                else tech=0;
            }
            if(tech) {
                if(unknown_6c16f0(-1)<0) {
                    if(tech->Health_Ratio()<Rules->unknown_1360 && House->Is_Ally(tech)) break;
                } else {
                    if(!House->Is_Ally(tech) || unknown_slot32()->AttackFriendlies
                       || (Kind_Of()==15 && (static_cast<InfantryClass *>(this)->unknown_5c0
                       || (static_cast<InfantryClass *>(this)->Type->Engineer && Mission==11
                           && tech->Health_Ratio()<=Rules->unknown_1370 && tech->Kind_Of()==6
                           && reinterpret_cast<TechnoTypeClass *>(static_cast<BuildingClass *>(tech)->Type)->unknown_slot33(reinterpret_cast<int>(tech->House))>0)))) break;
                }
            }
        }
        tentative=tentative->unknown_30;
    }
    if(!tech) return false;
    *object=tech;
    bool result=false;
    if(!House->Is_Ally(tech) || unknown_6c16f0(-1)<0
       || (!House->unknown_func_4f52f0() && this && Kind_Of()==15
           && As_Infantry(static_cast<FootClass *>(this))->Type->Engineer)) {
        result=unknown_6c5570(method,mask,range,tech,value,-1,&unknown_geometry_l);
    }
    return result;
}
