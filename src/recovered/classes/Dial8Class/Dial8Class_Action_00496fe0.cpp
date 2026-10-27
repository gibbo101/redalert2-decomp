#include "shared/dial8.hpp"
#include "shared/techno.hpp"
#include "shared/mouse.hpp"
#include "shared/fast_math.hpp"
extern int unknown_dial_drag_00852478;
// @ref ?unknown_dial_drag_00852478@@3HA=00852478
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Fast_Atan2@@YAMNN@Z=004ba600
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref __real@8@c00ca5f9836e4e441800=0079b628
inline UnknownFacingDir Dial_Direction(Point2D from, Point2D to)
{
    return UnknownFacingDir((unsigned short)((Fast_Atan2((double)from.Y - to.Y, (double)to.X - from.X) - 1.5707963267948966) * -10430.060040584269));
}
inline void Dial8Class::Update_Direction(unsigned direction)
{
    Direction = direction;
    Selected = Dir_To_8(UnknownFacingDir((unsigned short)(direction << 8)));
}
int Dial8Class::Action(unsigned flags, unsigned &key)
{
    Sticky_Process(flags);
    if (flags & LEFTPRESS) unknown_dial_drag_00852478 = 1;
    if ((flags & LEFTPRESS) || ((flags & LEFTHELD) && unknown_dial_drag_00852478)) {
        Update_Direction(Dir_To_256(Dial_Direction(Center, WWMouse->Get_Mouse_XY())));
        if (Selected != Previous) {
            Previous = Selected;
            ControlClass::Action(flags, key);
        } else {
            key = 0;
            ControlClass::Action(0, key);
        }
        return 1;
    }
    if (flags & LEFTRELEASE) {
        key = 0;
        unknown_dial_drag_00852478 = 0;
    }
    return ControlClass::Action(0, key);
}
