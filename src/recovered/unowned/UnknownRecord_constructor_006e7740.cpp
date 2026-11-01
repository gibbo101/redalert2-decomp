// ThemeControl::ThemeControl() (0x006E7740)
// An empty normal theme for any side (Init_Themes expands it inline).
#define THEME_CONTROL_RECORD
#include "shared/theme.hpp"

ThemeControl::ThemeControl() :
    Scenario(0),
    Duration(0),
    unknown_288(true),
    unknown_289(false),
    Available(false),
    Owner(-1)
{
    Name[0] = '\0';
    Sound[0] = '\0';
    FullName[0] = 0;
}
