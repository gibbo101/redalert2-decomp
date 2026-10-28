// void LineTrail::Clear_Owner() (0x005394F0)
#include "shared/line_trail.hpp"
#include "shared/object.hpp"

void LineTrail::Clear_Owner()
{
    if (Owner != 0) {
        Owner->unknown_94 = 0;
        Owner = 0;
    }
}
