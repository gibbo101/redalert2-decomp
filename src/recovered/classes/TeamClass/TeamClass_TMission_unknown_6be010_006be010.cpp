// void TeamClass::TMission_unknown_6be010(ScriptMissionClass const &mission, bool unknown) (0x006BE010)
#include "shared/team.hpp"
#include "shared/foot.hpp"
#include "shared/house.hpp"
#include "shared/super.hpp"
#include "shared/rules.hpp"
// Type-1 superweapon handler, twin of 0x006BE1C0: fires it at the team when ready,
// waits while it is charging within the rules' AI fraction, else completes the step.
inline void Complete_Step_006be010(TeamClass *team) { team->StepCompleted=true; }
void TeamClass::TMission_unknown_6be010(ScriptMissionClass const &mission, bool unknown)
{
    FootClass *leader=unknown_func_6baa60();
    if(!leader) { Complete_Step_006be010(this); return; }
    HouseClass *house=leader->House;
    SuperClass *weapon=0;
    int count=house->Supers.Count();
    for(int index=0;index<count;++index) {
        if(house->Supers[index]->Type->Type==1) {
            weapon=house->Supers[index];
            break;
        }
    }
    if(!weapon) { Complete_Step_006be010(this); return; }
    if(!weapon->unknown_0x57) {
        double remaining=weapon->RechargeTimer.Value();
        double total=weapon->Type->RechargeTime;
        if(weapon->unknown_0x55 && remaining/total <= 1.0f-Rules->unknown_b80) return;
        Complete_Step_006be010(this);
        return;
    }
    house->unknown_func_4e68d0(weapon->Type->Type,Coord_Cell(unknown_34->Center_Coord()));
    Complete_Step_006be010(this);
}
