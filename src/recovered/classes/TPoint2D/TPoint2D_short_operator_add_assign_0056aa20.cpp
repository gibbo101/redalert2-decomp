// TPoint2D<short>::operator+=, original0056AA20; only this original member is emitted.
#include "shared/map.hpp"
template <> TPoint2D<short> const &TPoint2D<short>::operator+=(TPoint2D<short> const &other)
{
    X += other.X;
    Y += other.Y;
    return *this;
}
