// bool MapClass::Unknown_0054AB00(CoordStruct const &coord) (0x0054AB00)
// The diamond test of 0x0054AAB0 for the cell of a lepton position
// (256 leptons per cell); the test is expanded inline.
#include "shared/map.hpp"

bool MapClass::Unknown_0054AB00(CoordStruct const &coord)
{
    short x = coord.X / 256;
    short y = coord.Y / 256;
    return Unknown_0054AAB0(Cell(x, y));
}
