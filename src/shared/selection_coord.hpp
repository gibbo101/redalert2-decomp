// Coord geometry model for the selection helpers. The non-polymorphic
// class name and hierarchy are source hypotheses from reference Coord/TPoint3D;
// three-int storage and original constructor0041B630 are independently evidenced.
#ifndef RA2_SHARED_SELECTION_COORD_HPP
#define RA2_SHARED_SELECTION_COORD_HPP
#include "shared/coord.hpp"
#include "shared/unknown_vector3.hpp"
inline UnknownVector3::UnknownVector3(int x,int y,int z):X(x),Y(y),Z(z) {}
class Coord:public UnknownVector3 {
public:
    Coord(int x,int y,int z):UnknownVector3(x,y,z) {}
    Coord(CoordStruct const &value) { X=value.X; Y=value.Y; Z=value.Z; }
    Coord(UnknownVector3 const &value):UnknownVector3(value) {}
};
#endif
