// bool RadarClass::Unknown_00630340(Cell const &cell) (0x00630340)
// Passes the call on (the radar adds nothing).
#include "shared/radar.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660

bool RadarClass::Unknown_00630340(Cell const &cell)
{
    return Unknown_0055A660(cell, true);
}
