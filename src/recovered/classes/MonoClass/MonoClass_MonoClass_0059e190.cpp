// MonoClass::MonoClass(int handle) (0x0059E190)
// Starts a blank 80 x 25 text window at the top left of the screen.
#include "shared/mono_class.hpp"
// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90

MonoClass::MonoClass(int handle)
{
    Handle = handle;
    X = 0;
    Y = 0;
    WindowX = 0;
    WindowY = 0;
    WindowWidth = 80;
    WindowHeight = 25;
    Clear();
}

void MonoClass::Set_Cursor(int x, int y)
{
    X = x;
    Y = y;
}

// @ref ?Refresh@MonoClass@@QAEXHHHH@Z=0059ea90
void MonoClass::Clear()
{
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            Characters[x][y] = ' ';
            Attributes[x][y] = 0;
        }
    }
    Changed = true;
    Refresh(0, 0, 80, 25);
}
