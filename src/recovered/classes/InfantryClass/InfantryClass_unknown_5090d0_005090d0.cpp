// bool InfantryClass::unknown_5090d0() const (0x005090D0)
// Whether the infantry is playing a deploy sequence (27-30); expanded
// inline in slots 137 and 291.
#include "shared/infantry.hpp"

bool InfantryClass::unknown_5090d0() const
{
    return Sequence == 27 || Sequence == 28 || Sequence == 29 || Sequence == 30;
}
