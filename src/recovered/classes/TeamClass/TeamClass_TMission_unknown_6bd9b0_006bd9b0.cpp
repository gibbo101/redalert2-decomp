// void TeamClass::TMission_unknown_6bd9b0(ScriptMissionClass const &mission, bool unknown) (0x006BD9B0)
// When flagged, creates the animation (type = low 16 bits of Data, loops = high 16 bits) at every member and attaches it.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/anim.hpp"
// @ref ?AnimTypes@@3V?$DynamicVectorClass@PAVAnimTypeClass@@@@A=008661e0
// @ref ?Attach_To@AnimClass@@QAEXPAVObjectClass@@@Z=00422540

void TeamClass::TMission_unknown_6bd9b0(ScriptMissionClass const &mission, bool unknown)
{
    int type = mission.Data & 0xFFFF;
    if (unknown && type >= 0 && type < AnimTypes.Count()) {
        FootClass *member = Member;
        unsigned int loops = mission.Data >> 16 & 0xFFFF;
        AnimTypeClass *anim_type = AnimTypes[type];
        if (member != 0) {
            do {
                AnimClass *anim = new AnimClass(anim_type, member->Center_Coord(), 0, loops, 0x600, 0);
                if (anim != 0) {
                    anim->Attach_To(member);
                }
                member = (FootClass *)member->unknown_4c8;
            } while (member != 0);
            StepCompleted = true;
            return;
        }
    }
    StepCompleted = true;
}
