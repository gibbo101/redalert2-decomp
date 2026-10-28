// void LineTrail::Delete_All() (0x005397B0)
#include "shared/line_trail.hpp"

void LineTrail::Delete_All()
{
    for (int index = 0; index < unknown_LineTrail_list_00a6e970.Count(); index++) {
        delete unknown_LineTrail_list_00a6e970[index];
    }
    unknown_LineTrail_list_00a6e970.Clear();
}
