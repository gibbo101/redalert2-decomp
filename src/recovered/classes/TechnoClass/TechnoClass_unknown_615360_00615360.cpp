#define RA2_COORD_EQUAL_MEMBER
// bool TechnoClass::unknown_615360() (0x00615360, PlanMgr.cpp)
// Starts carrying out the techno's planned path once: when its planning
// token has nodes, a first-node index of -1 or above 0 and is not started
// yet, queues mission 0x1C, lists the token's 0x00613330 event
// (Planning_Store_Event) and marks the token started.
#include "shared/planning.hpp"
// @ref ?unknown_613330@PlanningTokenClass@@QAE?AVEventClass@@XZ=00613330

bool TechnoClass::unknown_615360()
{
    PlanningTokenClass *token = Planning_Token(this);
    if (token != 0 && token->Nodes.Count() > 0 && (token->unknown_8c == -1 || token->unknown_8c > 0) && !token->unknown_1c) {
        unknown_slot116(0x1C, true);
        EventClass event = token->unknown_613330();
        Planning_Store_Event(event);
        token->unknown_1c = true;
        return true;
    }
    return false;
}
