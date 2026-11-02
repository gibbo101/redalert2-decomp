// ProgressScreenClass::Unknown_0061EFA0: text, row position and display flags.
#include "shared/progress_screen.hpp"
Rect __fastcall Unknown_006F1F30();
// @ref ?Unknown_006F1F30@@YI?AVRect@@XZ=006f1f30
void ProgressScreenClass::Unknown_0061EFA0(Point2D xy, wchar_t const *text, bool flag1, bool flag2)
{
    if (xy.X == -1 && xy.Y == -1) {
        int width = 0, height = 0;
        Box_Size(&width, &height, Count, flag1);
        Rect rect = Unknown_006F1F30();
        Position = Point2D((rect.Width - width) / 2, (rect.Height - height) / 2);
    } else {
        Position = xy;
    }
    Name = text;
    ShowFlags = flag1;
    unknown_71 = flag2;
}
