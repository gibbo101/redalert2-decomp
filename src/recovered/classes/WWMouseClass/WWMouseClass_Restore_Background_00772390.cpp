// void WWMouseClass::Restore_Background() (0x00772390)
// Copies Background back to the screen over the last cursor rectangle.
// Name is a hypothesis.
#include "shared/wwmouse.hpp"

void WWMouseClass::Restore_Background()
{
    if (BackgroundRect.Is_Valid() && ScreenSurface != 0 && Background != 0) {
        Rect toarea = BackgroundRect;
        toarea.X += ConfiningRect.X;
        toarea.Y += ConfiningRect.Y;
        ScreenSurface->Copy_From(toarea, *Background, Rect(0, 0, toarea.Width, toarea.Height), false,
                                 true);
    }
}
