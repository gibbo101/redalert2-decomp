#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Remove_Node(PlanningNodeClass *node) (0x00616960)
// Takes a node out of the paths of all its members (PlanningTokenClass
// 0x006138F0 on each member's token, last member first); the node after it in
// the first member's path (PlanningNodeClass::Next, expanded inline) is then
// rebuilt (0x00611EE0, 0x00611BD0 per member, 0x00611770) and marked not
// queued. Name hypothesis.
// The member loop is a file-local inline helper (hypothesis): written in place
// it leaves one /Ob2 site too many after Next, and Next's PlanningTokenClass::
// Node_At 0x00613C00 is then called out of line, where the original expands it.
#include "shared/planning.hpp"
// @ref ?unknown_6138f0@PlanningTokenClass@@QAEXH@Z=006138f0

static inline void Planning_Unlink_Node(PlanningNodeClass *node)
{
    for (int i = node->Members.Count() - 1; i >= 0; i--) {
        PlanningTokenClass *member_token = Planning_Token(node->Members[i]->Owner);
        member_token->unknown_6138f0(member_token->Node_Index(node));
    }
}

void __fastcall Planning_Remove_Node(PlanningNodeClass *node)
{
    if (node != 0) {
        PlanningNodeClass *next = node->Next(node->Members[0]->Owner);
        Planning_Unlink_Node(node);
        if (next != 0 && next != node) {
            next->unknown_611ee0();
            int count = next->Members.Count();
            for (int j = 0; j < count; j++) {
                next->unknown_611bd0(next->Members[j]);
            }
            next->unknown_611770();
            next->IsQueued = false;
        }
    }
}
