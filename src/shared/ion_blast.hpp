// IonBlastClass: an ion blast on the map (0x14 bytes, no vtable; the constructor
// 0x00521270 stores the coordinate, clears +0x0C and +0x10 and adds the blast to the
// list at 0x00A51F88; DynamicVectorClass<IonBlastClass *> per RTTI; field names are hypotheses).
#ifndef RA2_SHARED_ION_BLAST_HPP
#define RA2_SHARED_ION_BLAST_HPP

#include "shared/coord.hpp"

class IonBlastClass {
public:
    IonBlastClass(CoordStruct coord);       // 0x00521270

    CoordStruct Coord;                      // +0x00
    int unknown_0c;                         // +0x0C (0)
    int unknown_10;                         // +0x10 (0)
};

#endif
