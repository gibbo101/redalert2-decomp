// bool MapClass::Unknown_0054AB00(CoordStruct const &coord) (0x0054AB00)
// The diamond test of 0x0054AAB0 for the cell of a lepton position
// (256 leptons per cell); the test is expanded inline.
#include "shared/map.hpp"

bool MapClass::Unknown_0054AB00(CoordStruct const &coord)
{
    return Unknown_0054AAB0(Cell(coord.X / 256, coord.Y / 256));
}
