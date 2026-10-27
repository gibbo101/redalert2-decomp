// A three-component offset with an out-of-line constructor (0x0041B630)
// and length (0x0041B780) (hypothesis: a coordinate difference class).
// Proposal: moved here from shared/display.hpp (which would include this
// header) so units that cannot include display.hpp can use it.
#ifndef RA2_SHARED_UNKNOWN_VECTOR3_HPP
#define RA2_SHARED_UNKNOWN_VECTOR3_HPP

struct UnknownVector3 {
    UnknownVector3() {}
    UnknownVector3(int x, int y, int z);
    int Length() const;
    int X;
    int Y;
    int Z;
};

#endif
