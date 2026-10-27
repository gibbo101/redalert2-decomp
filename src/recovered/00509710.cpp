#include "shared/infantry.hpp"
// Sequence check (receiver unused; member ABI hypothesis).
bool InfantryClass::Is_Busy_Sequence_00509710(int sequence) const
{
    return sequence == 11 || sequence == 12 || sequence == 13 || sequence == 14 || sequence == 15
        || sequence == 34 || sequence == 35 || sequence == 36 || sequence == 20 || sequence == 21;
}
