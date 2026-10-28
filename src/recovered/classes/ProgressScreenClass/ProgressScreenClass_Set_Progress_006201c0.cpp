// void ProgressScreenClass::Set_Progress_006201c0(int index, double value, Point2D point) (0x006201C0)
// Sets a player's progress to value percent of the total (at most the
// total); when it changed, repaints the window or redraws at point. The
// listener (while the screen is active) is told the mean percent before and
// after.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"

void ProgressScreenClass::Set_Progress_006201c0(int index, double value, Point2D point)
{
    int before = Average_Progress() * 100.0;
    double old = Progress[index];
    Progress[index] = (Total * 0.01) * value;
    if (Progress[index] > Total) {
        Progress[index] = Total;
    }
    if (old != Progress[index]) {
        if (Window != 0) {
            SendMessageA(Window, 0x0F, 0, 0);
        } else {
            Draw_It(point);
        }
    }
    int after = Average_Progress() * 100.0;
    int percent[2] = { before, after };
    if (Listener != 0 && unknown_60) {
        Listener->Message_00536ea0(0x11AE, percent);
    }
}
