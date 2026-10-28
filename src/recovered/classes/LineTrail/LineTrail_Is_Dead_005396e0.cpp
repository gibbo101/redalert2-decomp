// int LineTrail::Is_Dead() const (0x005396E0)
#include "shared/line_trail.hpp"

int LineTrail::Is_Dead() const
{
    return Owner == 0 && Trails[ActiveSlot].Value == 0;
}
