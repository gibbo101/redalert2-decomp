#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Remove_Member(TechnoClass *techno) (0x00610E70)
// Takes techno's member out of the node: out of its branches, then frees its
// order copy and the member; a node left without members deletes itself.
#include "shared/planning.hpp"
// @ref ?Add@?$DynamicVectorClass@PAVPlanningNodeClass@@@@QAE_NABQAVPlanningNodeClass@@@Z=0061b300

void PlanningNodeClass::Remove_Member(TechnoClass *techno)
{
    PlanningMemberClass *member = Member_For(techno);
    if (member != 0) {
        unknown_611e20(member);
        delete member->Get_Event();
        Members.Delete(member);
        delete member;
        if (Members.Count() == 0) {
            delete this;
        }
    }
}
