#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_6144f0() (0x006144F0)
// Removes this token from the static list unknown_list_00a76738 unless the
// planning lists are being torn down.
#include "shared/planning.hpp"
// @ref ?unknown_flag_a767a5@@3_NA=00a767a5

void PlanningTokenClass::unknown_6144f0()
{
    PlanningTokenClass *token = this;
    if (!unknown_flag_a767a5) {
        unknown_list_00a76738.Delete(token);
    }
}
