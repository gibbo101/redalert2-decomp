#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Index_For(TechnoClass *techno) (0x00610C30)
#include "shared/planning.hpp"

int PlanningNodeClass::Index_For(TechnoClass *techno)
{
    PlanningTokenClass *token = Planning_Token(techno);
    return token->Nodes.ID(this);
}
