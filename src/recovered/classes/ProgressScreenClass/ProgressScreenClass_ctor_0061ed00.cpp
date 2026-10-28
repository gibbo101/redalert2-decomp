// ProgressScreenClass::ProgressScreenClass() (0x0061ED00)
#include "shared/progress_screen.hpp"

ProgressScreenClass::ProgressScreenClass() :
    Total(0),
    Name(0),
    Shape(0),
    ShapeAllocated(false),
    Image(0),
    unknown_60(false),
    Count(0),
    unknown_62(false),
    Window(0),
    Position(0, 0),
    ShowFlags(false),
    NameWidth(-1),
    unknown_7c(0),
    Side(-1)
{
    for (int index = 0; index < 8; index++) {
        Progress[index] = 0;
    }
}
