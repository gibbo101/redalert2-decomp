// Coord geometry model for the selection helpers (TibSun Coord over the map coordinate;
// hypothesis: here a CoordStruct with a forwarding (x, y, z) constructor).
#ifndef RA2_SHARED_SELECTION_COORD_HPP
#define RA2_SHARED_SELECTION_COORD_HPP
#include "shared/coord.hpp"
class Coord : public CoordStruct {
public:
    Coord(int x, int y, int z) : CoordStruct(x, y, z) {}
    Coord(CoordStruct const &coord) : CoordStruct(coord) {}
};
#endif
