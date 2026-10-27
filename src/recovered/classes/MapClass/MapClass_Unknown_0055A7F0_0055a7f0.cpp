// bool MapClass::Unknown_0055A7F0(CoordStruct const &coord) (0x0055A7F0)
// The cell test 0x0055A660 (with true) for the cell of a lepton position.
#include "shared/map.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660

bool MapClass::Unknown_0055A7F0(CoordStruct const &coord)
{
    Cell cell = Cell(coord.X / 256, coord.Y / 256);
    return Unknown_0055A660(cell, true);
}
