#include "shared/infantry.hpp"
// Prone/crawling animation states (receiver unused; member ABI hypothesis).
bool InfantryClass::Is_Prone_Sequence_005096e0(int sequence) const
{
    if (sequence != 9 && sequence != 10 && sequence != 18 && sequence != 19
        && sequence != 23 && sequence != 32) {
        return false;
    }
    return true;
}
