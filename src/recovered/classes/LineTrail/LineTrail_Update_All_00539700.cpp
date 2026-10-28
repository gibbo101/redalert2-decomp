// void LineTrail::Update_All() (0x00539700)
#include "shared/line_trail.hpp"
// @ref ?Draw@LineTrail@@QAEXXZ=005395c0
// @ref ?AI@LineTrail@@QAEXXZ=00539530

void LineTrail::Update_All()
{
    for (int index = unknown_LineTrail_list_00a6e970.Count() - 1; index >= 0; index--) {
        LineTrail *trail = unknown_LineTrail_list_00a6e970[index];
        trail->AI();
        if (trail->Is_Dead()) {
            delete trail;
        } else {
            trail->Draw();
        }
    }
}
