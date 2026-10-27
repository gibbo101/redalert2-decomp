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
