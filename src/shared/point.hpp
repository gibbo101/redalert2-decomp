// Westwood's library point template TPoint2D<T> (TibSun point.h): a point in
// two dimensions with member-wise arithmetic. Cell (shared/coord.hpp) is a
// TPoint2D<short>. The operators return `TPoint2D<T> const` built with T(...)
// casts, as in TibSun: /Ob2 then charges a sum or difference about 64 IL units
// with a free nested constructor, which is what the original's inline decisions
// in Map.CPP (Destroy_Low_Bridge_Span 0x00556BF0) and its out-of-line copies
// reproduce (InlineLab398, CellModel400). Only the members the recovered code
// uses are declared.
#ifndef RA2_SHARED_POINT_HPP
#define RA2_SHARED_POINT_HPP

template<class T>
class TPoint2D {
public:
    TPoint2D() {}
    TPoint2D(T x, T y) : X(x), Y(y) {}

    // Member-wise addition in place, reference point arithmetic.
#ifdef RA2_POINT_ADD_IN_PLACE_SOURCE
    TPoint2D<T> const &operator+=(TPoint2D<T> const &rvalue);
#elif defined(RA2_POINT_ADD_IN_PLACE)
    TPoint2D<T> const &operator+=(TPoint2D<T> const &rvalue) { X += rvalue.X; Y += rvalue.Y; return *this; }
#endif
    TPoint2D<T> const &operator-=(TPoint2D<T> const &rvalue) { X -= rvalue.X; Y -= rvalue.Y; return *this; }
    // Member-wise difference and sum (TPoint2D<short>: out-of-line copies
    // 0x0056AA40 in Map.CPP and 0x0042ADD0).
    TPoint2D<T> const operator-(TPoint2D<T> const &rvalue) const { return TPoint2D<T>(T(X - rvalue.X), T(Y - rvalue.Y)); }
    TPoint2D<T> const operator+(TPoint2D<T> const &rvalue) const { return TPoint2D<T>(T(X + rvalue.X), T(Y + rvalue.Y)); }

    TPoint2D<T> const operator/(T rvalue) const { if (rvalue == T(0)) return TPoint2D<T>(0, 0); return TPoint2D<T>(T(X / rvalue), T(Y / rvalue)); }

    TPoint2D<T> const operator-() const { return TPoint2D<T>(T(-X), T(-Y)); }

#ifdef RA2_POINT_LENGTH
    // TibSun point.h's length through the fast square root and the distance
    // built on it (RadarEvent.cpp's suppression test, 0x0063B5B0). Guarded:
    // shared/fast_math.hpp must be included first.
    T Length() const { return T(Fast_Sqrt((double)X * (double)X + (double)Y * (double)Y)); }
    T Distance_To(TPoint2D<T> const &point) const { return (*this - point).Length(); }
#endif

    T X;
    T Y;
};

#endif
