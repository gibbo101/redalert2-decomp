// void BinkClass::Unknown_00430820() (0x00430820)
// Copies the current frame into the target surface again at the movie area
// (offset by the window client area on the screen surface).
#include "shared/movie.hpp"

void BinkClass::Unknown_00430820()
{
    if (Target == unknown_surface_839950) {
        RECT client;
        GetClientRect(MainWindow, &client);
        ClientToScreen(MainWindow, (POINT *)&client);
        int x = Area.X + client.left;
        int y = Area.Y + client.top;
        Unknown_00430940(Target, x, y);
    } else {
        Unknown_00430940(Target, Area.X, Area.Y);
    }
}
