#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Path_Add(TechnoClass *techno, PlanningNodeClass *node) (0x00616350)
// Gives the techno a planning token if it has none, then closes its path
// into a loop at the node when the path holds it already, else appends it.
#include "shared/planning.hpp"
// @ref ??0?$VectorClass@PAVPlanningNodeClass@@@@QAE@IPBQAVPlanningNodeClass@@@Z=0061bd70
// @ref ?Planning_Path_Append@@YIXPAVTechnoClass@@PAVPlanningNodeClass@@@Z=006165a0

void __fastcall Planning_Path_Add(TechnoClass *techno, PlanningNodeClass *node)
{
    PlanningTokenClass *token = Planning_Token(techno);
    if (!token) {
        token = Planning_New_Token(techno);
    }
    if (token->Node_Index(node) != -1) {
        Planning_Close_Loop(techno, node);
    } else {
        Planning_Path_Append(techno, node);
    }
}
