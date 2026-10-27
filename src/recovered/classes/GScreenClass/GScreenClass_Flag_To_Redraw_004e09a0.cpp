// void GScreenClass::Flag_To_Redraw(int complete) (0x004E09A0, slot 14)
// Marks the tactical view dirty; a nonzero request is remembered unless a
// complete redraw is already pending, and the screen object is notified.
#include "shared/gscreen.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0055ACC0@MapClass@@QAEXXZ=0055acc0
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c

void GScreenClass::Flag_To_Redraw(int complete)
{
    if (unknown_tactical_83996c != 0) {
        unknown_tactical_83996c->unknown_d7d = true;
    }
    if (complete) {
        if (IsToRedraw != 2) {
            IsToRedraw = complete;
        }
        Map.Unknown_0055ACC0();
    }
}
