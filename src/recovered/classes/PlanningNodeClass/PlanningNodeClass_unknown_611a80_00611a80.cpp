#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::unknown_611a80(TechnoClass *techno) (0x00611A80)
// The index of the branch whose event lies at the coordinate of the
// techno's event on the previous node of its path, or -1 (also -1 when the
// previous node is the path's last node). Names are hypotheses.
// Previous (0x00610C60), the token's Last_Node and Event_For (Member_For with
// Member_Index 0x00611050 called) are expanded inline; the branch coordinate
// is a named local compared with operator== (0x0061A8B0, expanded).
#include "shared/planning.hpp"

int PlanningNodeClass::unknown_611a80(TechnoClass *techno)
{
    PlanningNodeClass *previous = Previous(techno);
    if (previous != Planning_Token(techno)->Last_Node()) {
        EventClass event = previous->Event_For(techno);
        int count = Branches.Count();
        if (count != 0) {
            CoordStruct coord = Planning_Event_Coord(event);
            for (int index = 0; index < count; index++) {
                PlanningBranchClass *branch = Branches[index];
                if (branch->Get_Count() != 0) {
                    CoordStruct branch_coord = Planning_Event_Coord(branch->Get_Event());
                    if (coord == branch_coord) {
                        return index;
                    }
                }
            }
        }
    }
    return -1;
}
