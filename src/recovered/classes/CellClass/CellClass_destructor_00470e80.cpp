// CellClass::~CellClass() (0x00470E80): deletes the fogged-object list and
// the owned +0xFC object, clears the occupier and, for a cell other than the
// zero cell, releases +0x34 (its count drops while unknown_flag_a40958 is set).
#include "shared/cell.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/light_convert.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958

CellClass::~CellClass()
{
    if (FoggedObjects != 0) {
        delete FoggedObjects;
        FoggedObjects = 0;
    }
    if (unknown_fc != 0) {
        delete unknown_fc;
        unknown_fc = 0;
    }
    OccupierPtr = 0;
    if (MapCoords != unknown_geometry_k && unknown_34 != 0) {
        if (unknown_flag_a40958) {
            unknown_34->unknown_194--;
        }
        unknown_34 = 0;
    }
}
