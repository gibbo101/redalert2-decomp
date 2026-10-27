#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Refuse(char const *label) (0x00616FD0)
// Once per planning session: shows the refusal message and plays the
// refused-action sound.
#include "shared/planning.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_flag_a766c8@@3_NA=00a766c8

void __fastcall Planning_Refuse(char const *label)
{
    if (!unknown_flag_a766c8) {
        unknown_flag_a766c8 = true;
        Planning_Message(label);
        Unknown_00713DB0(Rules->unknown_620, 1.0f, 0x2000, 0);
    }
}
