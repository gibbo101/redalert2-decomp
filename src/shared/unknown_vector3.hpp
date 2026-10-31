// A three-component offset with an out-of-line constructor (0x0041B630)
// and length (0x0041B780) (hypothesis: a coordinate difference class).
// Proposal: moved here from shared/display.hpp (which would include this
// header) so units that cannot include display.hpp can use it.
#ifndef RA2_SHARED_UNKNOWN_VECTOR3_HPP
#define RA2_SHARED_UNKNOWN_VECTOR3_HPP

struct UnknownVector3 {
    UnknownVector3() {}
    UnknownVector3(int x, int y, int z);
    UnknownVector3 const operator+(UnknownVector3 const &other) const
    { return UnknownVector3(X+other.X,Y+other.Y,Z+other.Z); }
    UnknownVector3 const operator/(int divisor) const
    {
        if (divisor==0) return UnknownVector3(0,0,0);
        return UnknownVector3(X/divisor,Y/divisor,Z/divisor);
    }
    int Length() const;
    UnknownVector3 const operator-(UnknownVector3 const &other) const
    {
        return UnknownVector3(X-other.X, Y-other.Y, Z-other.Z);
    }
    int Distance_To(UnknownVector3 const &other) const
    {
        return (*this-other).Length();
    }
    int X;
    int Y;
    int Z;
};

#endif
