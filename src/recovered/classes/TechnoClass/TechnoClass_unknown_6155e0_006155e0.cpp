#define RA2_COORD_EQUAL_MEMBER
// void TechnoClass::unknown_6155e0() (0x006155E0)
// Drops the techno's planned path: its token's members leave every node and
// the token is cleared (PlanningTokenClass::unknown_612ec0, expanded inline
// with Remove_Member and Planning_Unlist_Techno).
#include "shared/planning.hpp"

void TechnoClass::unknown_6155e0()
{
    PlanningTokenClass *token = Planning_Token(this);
    if (token != 0) {
        token->unknown_612ec0();
    }
}
