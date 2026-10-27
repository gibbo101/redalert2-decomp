#define RA2_COORD_EQUAL_MEMBER
// void __fastcall Planning_Uncount(int house) (0x00616D20)
// Lowers a house's counter (never below 0).
#include "shared/planning.hpp"
// @ref ?unknown_counts_a76684@@3PAHA=00a76684

void __fastcall Planning_Uncount(int house)
{
    if (house >= 0 && house < 8) {
        int value = unknown_counts_a76684[house] - 1;
        unknown_counts_a76684[house] = value < 0 ? 0 : value;
    }
}
