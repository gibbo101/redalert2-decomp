#define RA2_COORD_EQUAL_MEMBER
// void TechnoClass::unknown_6145e0() (0x006145E0)
// With planning active: tells every member of the last node on the techno's
// planned path to stop (their slot 80), unless they are already finished.
// The flag keeps it from re-entering.
#include "shared/planning.hpp"
// @ref ?unknown_flag_a767a6@@3_NA=00a767a6
// @ref ?unknown_flag_a767a4@@3_NA=00a767a4

void TechnoClass::unknown_6145e0()
{
    if (!unknown_flag_a767a6) {
        unknown_flag_a767a6 = true;
        if (unknown_flag_a767a4) {
            PlanningTokenClass *token = Planning_Token(this);
            if (token) {
                PlanningNodeClass *last = token->Last_Node();
                if (last) {
                    last->unknown_612090();
                }
            }
        }
        unknown_flag_a767a6 = false;
    }
}
