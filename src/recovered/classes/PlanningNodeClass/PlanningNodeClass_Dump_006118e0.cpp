#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::Dump() const (0x006118E0)
// Debug output: every branch and the loop branch with their members.
#include "shared/planning.hpp"
// @ref ??_C@_0EE@OHFO@Branch?5?$FL?$CFd?$FN?$DL?5?5Member?5count?$FL?$CFd?$FN?$DL?5@=007ebcc0
// @ref ??_C@_0EJ@FLKL@Loop?5Branch?5?$FL?$CFd?$FN?$DL?5?5Member?5count?$FL@=007ebc4c
// @ref ??_C@_0CH@HNNK@?5?5Member?5?$FL?$CFs?$FN?$DL?5?5Cell?5location?$FL?$CFd@=007ebc98

void PlanningNodeClass::Dump() const
{
    int branches = Branches.Count();
    for (int b = 0; b < branches; b++) {
        PlanningBranchClass *branch = Branches[b];
        int count = branch->Count;
        EventClass event = branch->Event;
        CoordStruct coord = Planning_Event_Coord(event);
        Debug_Printf("Branch [%d];  Member count[%d];  Origin event location[%d, %d, %d]\n", b, count, coord.X, coord.Y, coord.Z);
        int members = Members.Count();
        for (int m = 0; m < members; m++) {
            PlanningMemberClass *member = Members[m];
            if (member->BranchIndex == b) {
                TechnoClass *techno = member->Owner;
                char const *name = techno->Class_Of()->ID;
                Cell cell = techno->unknown_slot104();
                Debug_Printf("  Member [%s];  Cell location[%d, %d]\n", name, cell.X, cell.Y);
            }
        }
    }
    int loop_count = Branch.Count;
    if (loop_count > 0) {
        EventClass event = Branch.Event;
        CoordStruct coord = Planning_Event_Coord(event);
        Debug_Printf("Loop Branch [%d];  Member count[%d];  Origin event location[%d, %d, %d]\n", unknown_b0, loop_count, coord.X, coord.Y, coord.Z);
        int members = Members.Count();
        for (int m = 0; m < members; m++) {
            PlanningMemberClass *member = Members[m];
            if (member->unknown_0c) {
                TechnoClass *techno = member->Owner;
                char const *name = techno->Class_Of()->ID;
                Cell cell = techno->unknown_slot104();
                Debug_Printf("  Member [%s];  Cell location[%d, %d]\n", name, cell.X, cell.Y);
            }
        }
    }
}
