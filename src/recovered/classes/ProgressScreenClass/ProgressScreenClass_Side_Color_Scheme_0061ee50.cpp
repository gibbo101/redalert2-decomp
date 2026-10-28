// ColorScheme *ProgressScreenClass::Side_Color_Scheme() (0x0061EE50)
// The loading screen's colours: Allied for side 0, Soviet otherwise.
#include "shared/progress_screen.hpp"
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
// @ref ??_C@_0L@FJPD@AlliedLoad?$AA@=007ebfb8
// @ref ??_C@_0L@KNBO@SovietLoad?$AA@=007ebfac

ColorScheme *ProgressScreenClass::Side_Color_Scheme()
{
    if (Side == 0) {
        return unknown_color_scheme_663d30("AlliedLoad", 1);
    }
    return unknown_color_scheme_663d30("SovietLoad", 1);
}
