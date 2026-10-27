// int DisplayClass::TacticalClass::Action(unsigned flags, unsigned &key) (0x0049AE70, slot 31)
// The tactical area's gadget: takes the mouse point (the queued one for a
// mouse key, else the live one), finds the cell, coordinate and object under
// it (ScrollClass 0x00669650) and moves the cursor cell there when it
// changed, then lets GadgetClass handle the key.
#include "shared/display.hpp"
#include "shared/mouse.hpp"
#include "shared/keyboard.hpp"
#include "shared/tactical.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_004994D0@DisplayClass@@QAE?AVCell@@ABV2@@Z=004994d0
// @ref ?Unknown_00669650@ScrollClass@@QAE_NABUPoint2D@@AAVCell@@AAUCoordStruct@@AAPAVObjectClass@@AA_N4@Z=00669650

int DisplayClass::TacticalClass::Action(unsigned flags, unsigned &key)
{
    ObjectClass *object = 0;
    Point2D xy;
    xy.X = 0;
    xy.Y = 0;
    if (flags & 0x55) {
        xy = Point2D(WWKeyboard->MouseQX, WWKeyboard->MouseQY);
    } else {
        WWMouse->Get_Mouse_X();
        WWMouse->Get_Mouse_Y();
        xy = WWMouse->Get_Mouse_XY();
    }
    unknown_tactical_83996c->Unknown_006A2B10(xy);
    xy -= Point2D(unknown_rect_839630.X, unknown_rect_839630.Y);
    Cell cell;
    CoordStruct coord;
    bool arg5;
    bool arg6;
    Map.Unknown_00669650(xy, cell, coord, object, arg5, arg6);
    if (cell != Map.unknown_1170) {
        Map.Unknown_004994D0(cell);
    }
    return GadgetClass::Action(0, key);
}
