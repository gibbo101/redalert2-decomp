// LineTrail::~LineTrail() (0x00539490)
#include "shared/line_trail.hpp"

LineTrail::~LineTrail()
{
    Clear_Owner();
    unknown_LineTrail_list_00a6e970.Delete(this);
}
