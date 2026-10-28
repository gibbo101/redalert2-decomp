// void ProgressScreenClass::Add_Progress(int index, double value, Point2D point) (0x006202C0)
// Adds value percent of the total to a player's progress (at most the
// total); when it changed, repaints the window or redraws at point. The
// listener is told the mean percent before and
// after.
#include "shared/progress_screen.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"

void ProgressScreenClass::Add_Progress(int index, double value, Point2D point)
{
    int before = Average_Progress() * 100.0;
    double old = Progress[index];
    Progress[index] += (Total * 0.01) * value;
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
    if (Listener != 0) {
        Listener->Message_00536ea0(0x11AE, percent);
    }
}
