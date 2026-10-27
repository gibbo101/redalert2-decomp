#define RA2_COORD_EQUAL_MEMBER
// int __fastcall Planning_Count(int house) (0x00616D50)
// A house's counter (0 for a house number out of range).
#include "shared/planning.hpp"

int __fastcall Planning_Count(int house)
{
    bool valid;
    if (house >= 0 && house < 8) {
        valid = true;
    } else {
        valid = false;
    }
    int count = 0;
    if (valid) {
        count = unknown_counts_a76684[house];
    }
    return count;
}
