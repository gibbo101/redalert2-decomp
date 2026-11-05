#define RA2_COORD_EQUAL_MEMBER
// EventClass PlanningTokenClass::unknown_613330() (0x00613330)
// Consumes the first planned event: the first node leaves the path and either
// rejoins it at the end (a loop at its start) or loses the owner, then the
// first-node index steps down and an emptied path unlists the owner.
#include "shared/planning.hpp"
// @ref ?Delete@?$DynamicVectorClass@PAVTechnoClass@@@@QAE_NH@Z=0061bdc0

template<class T> inline T Max(T a, T b) { return a > b ? a : b; }

// The owner's event at a node, kept as the token's current event.
static inline EventClass Take_Event(PlanningNodeClass *node, TechnoClass *owner, EventClass &current)
{
    EventClass event = node->Event_For(owner);
    current = event;
    return event;
}

// Steps the first-node index down and unlists an owner with no path left.
static inline void Finish_Step(PlanningTokenClass *token)
{
    token->unknown_8c = Max(-1, token->unknown_8c - 1);
    if (token->Nodes.Count() == 0) {
        Planning_Unlist_Techno(token->Owner);
    }
}

EventClass PlanningTokenClass::unknown_613330()
{
    PlanningNodeClass *node = Nodes[0];
    EventClass event = Take_Event(node, Owner, Event);
    Nodes.Delete(0);
    if (LoopStart == 0) {
        unknown_99 = true;
        Nodes.Add(node);
        Planning_Queue_Node(node);
    } else {
        node->Remove_Member(Owner);
        if (LoopStart > 0) {
            --LoopStart;
            LoopStart = Max(Get_LoopStart(), 0);
        }
    }
    Finish_Step(this);
    return event;
}
