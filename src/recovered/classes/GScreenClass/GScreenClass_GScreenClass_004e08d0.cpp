// GScreenClass::GScreenClass() (0x004E08D0)
// Clears the shake offsets and asks for a complete first redraw.
#include "shared/gscreen.hpp"
// @ref ??_7GScreenClass@@6B@=007a2c3c

GScreenClass::GScreenClass() : ShakeX(0), ShakeY(0), IsToRedraw(2)
{
}
