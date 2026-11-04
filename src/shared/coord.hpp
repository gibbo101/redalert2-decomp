// Map coordinates: CoordStruct (leptons, x/y/z) and Cell (cell x/y).
// Layouts from AbstractClass/ObjectClass (Center_Coord returns a
// CoordStruct) and the per-unit zero constants of
// shared/unknown_geometry.hpp. Names follow Westwood's TS/RA2 vocabulary.
#ifndef RA2_SHARED_COORD_HPP
#define RA2_SHARED_COORD_HPP

#include "shared/point.hpp"

struct INIPoint3D;
#ifdef RA2_BUILDING_DELAY_POINT
template<class T> struct TPoint3D;
#endif
#if defined(RA2_LOCOMOTION_COM_VALUE_TYPES) || defined(RA2_SHIP_MOVE_TO_VALUE)
// Plain COM coordinate returned by ILocomotion; three ordered signed DWORDs.
struct COMCoordStruct { int X, Y, Z; };
#endif
#ifdef RA2_COORD_PLUS_POINT2D
struct Point2D;
#endif

#if defined(RA2_COORD_AS_CELL) || defined(RA2_COORD_FROM_CELL) || defined(RA2_COORD_FROM_CELL_INLINE)
class Cell;
#endif
#ifdef RA2_TPOINT3D_DIFFERENCE
double __cdecl unknown_sqrt_4ba410(double value);     // 0x004BA410
#endif
#ifdef RA2_COORD_TPOINT3D
// Coord's point base (layout and sum hypothesis evidenced by AnimClass 00420110).
template<class T> class TPoint3D : public TPoint2D<T> {
public:
    TPoint3D() {}
    TPoint3D(T x, T y, T z) : TPoint2D<T>(x, y), Z(z) {}
    TPoint3D<T> const operator+(TPoint3D<T> const &point) const {
#ifdef RA2_TPOINT3D_SUM_X_LOCAL
        T x = this->X;
        return TPoint3D<T>(x + point.X, this->Y + point.Y, Z + point.Z);
#else
        return TPoint3D<T>(this->X + point.X, this->Y + point.Y, Z + point.Z);
#endif
    }
#ifdef RA2_TPOINT3D_DIFFERENCE
    // TibSun point.h: the member-wise difference and the length through the fast square root.
    TPoint3D<T> const operator-(TPoint3D<T> const &point) const { return TPoint3D<T>(this->X - point.X, this->Y - point.Y, Z - point.Z); }
    // Separate from the out-of-line 0x0041B780 (owner ruling): x, y, z through the fast square root.
    T Length() const { double x = this->X; double y = this->Y; double z = Z; return T(unknown_sqrt_4ba410(x * x + (y * y + z * z))); }
#ifdef RA2_SHIP_SOM
    T Distance_To(TPoint3D<T> const &point) const { return (*this - point).Length(); }
    T Length_YZX() const { double y = this->Y; double z = Z; double x = this->X; return T(unknown_sqrt_4ba410(y * y + (z * z + x * x))); }
    T Distance_YZX(TPoint3D<T> const &point) const { return (*this - point).Length_YZX(); }
#endif
#endif
    T Z;
};
struct CoordStruct : public TPoint3D<int> {
    typedef TPoint3D<int> BASECLASS;
    CoordStruct(BASECLASS const &point) : BASECLASS(point) {}
#else
struct CoordStruct {
#endif
    CoordStruct() {}
#ifdef RA2_BUILDING_DELAY_POINT
    CoordStruct(TPoint3D<int> const &point);
#endif
#ifdef RA2_SHIP_MOVE_TO_VALUE
    operator COMCoordStruct() const { COMCoordStruct result; result.X=X; result.Y=Y; result.Z=Z; return result; }
#endif
#if defined(RA2_LOCOMOTION_COM_VALUE_TYPES) || defined(RA2_SHIP_MOVE_TO_VALUE)
    CoordStruct(COMCoordStruct const &coord) { X = coord.X; Y = coord.Y; Z = coord.Z; }
#endif
#ifdef RA2_COORD_TPOINT3D
    CoordStruct(int x, int y, int z) : BASECLASS(x, y, z) {}
#else
    CoordStruct(int x, int y, int z) : X(x), Y(y), Z(z) {}
#endif
#ifdef RA2_COORD_LENGTH
    // Euclidean length, out of line at 0x0041B780 (accepted as
    // UnknownVector3::Length: UnknownVector3 is this struct under a
    // placeholder name). Guarded: the unit defines RA2_COORD_LENGTH before
    // its first include of this header.
    int Length() const;
#endif
#ifdef RA2_COORD_POINT_Z
    // TibSun Coord(TPoint2D, z): a point at a height.
    inline CoordStruct(struct Point2D const &point, int z);
#endif
#ifdef RA2_COORD_FROM_CELL_INLINE
    // The centre of a cell at height z (out of line 0x0061EA80; inline in Building.cpp).
    CoordStruct(Cell const &cell, int z = 0);
#endif
    // From the point an INI reader returns (defined in shared/ini_class.hpp).
    CoordStruct(INIPoint3D const &point);
    // Member-wise difference (0x004348F0 is the out-of-line copy the BuildingLight unit keeps).
#ifdef RA2_TPOINT3D_DIFFERENCE
    using BASECLASS::operator-;
#elif defined(RA2_COORD_MINUS_SOURCE)
    // The member's own source supplies the independently bounded out-of-line copy.
    CoordStruct operator-(CoordStruct const &coord) const;
#else
    CoordStruct operator-(CoordStruct const &coord) const
    {
        return CoordStruct(X - coord.X, Y - coord.Y, Z - coord.Z);
    }
#endif
#ifdef RA2_COORD_PLUS_POINT2D
    // TibSun TPoint3D + TPoint2D: X and Y summed, Z kept (Adjacent_Coord_With_Height 0x00491880).
    // Guarded: the coord.cpp unit (0x00491430) defines RA2_COORD_PLUS_POINT2D before its first include.
    CoordStruct const operator+(Point2D const &point) const;
#endif
    // Member-wise sum (AnimClass::Center_Coord, 0x00420D90).
    // Member-wise difference in place (Tactical::Coord_To_Cell 0x006A6A50 steps back with it; its Z store stays).
    CoordStruct &operator-=(CoordStruct const &coord) { X -= coord.X; Y -= coord.Y; Z -= coord.Z; return *this; }
    // Member-wise sum in place (DisplayClass::Center_Map 0x0049E3B0).
    CoordStruct const &operator+=(CoordStruct const &coord) { X += coord.X; Y += coord.Y; Z += coord.Z; return *this; }
    // Member-wise quotient in place; a zero divisor leaves the coordinate (0x0049E3B0).
    CoordStruct const &operator/=(int divisor) { if (divisor != 0) { X /= divisor; Y /= divisor; Z /= divisor; } return *this; }
#ifdef RA2_COORD_PLUS_SOURCE
    CoordStruct operator+(CoordStruct const &coord) const;
#else
#ifdef RA2_COORD_TPOINT3D
    using BASECLASS::operator+;
#else
    CoordStruct operator+(CoordStruct const &coord) const
    {
        return CoordStruct(X + coord.X, Y + coord.Y, Z + coord.Z);
    }
#endif
#endif
#ifdef RA2_COORD_EQUAL_MEMBER
    // Member-wise comparison (0x0061A8B0): the original has a real out-of-line
    // int-returning thiscall member that Planning.cpp calls, while the
    // locomotors use an inline free bool comparison (shared/locomotion.hpp);
    // the two forms coexisted in different translation units. Only the
    // Planning unit defines RA2_COORD_EQUAL_MEMBER (first line of its first
    // draft), so no other unit sees this declaration.
    int operator==(CoordStruct const &coord) const;
#endif
    // Member-wise quotient; a zero divisor gives (0, 0, 0). Inline as in TibSun's TPoint3D
    // (DisplayClass::Center_Map 0x0049E3B0 expands it). 0x006D9770 is the out-of-line copy the
    // Techno unit emits for its non-inlined calls in 0x006C2C40, which is not recovered yet: until
    // it is, that unit defines RA2_COORD_DIVIDE_SOURCE (first line of its first draft) and the
    // row's own source supplies the copy; then the define and that definition go.
#ifdef RA2_COORD_TIMES
    CoordStruct const operator*(int value) const
    {
        return CoordStruct(X * value, Y * value, Z * value);
    }
#endif
#ifdef RA2_COORD_DIVIDE_SOURCE
    CoordStruct operator/(int divisor) const;
#else
    CoordStruct operator/(int divisor) const
    {
        if (divisor == 0) {
            return CoordStruct(0, 0, 0);
        }
        return CoordStruct(X / divisor, Y / divisor, Z / divisor);
    }
#endif
    // EAX=this/ret12; returned-reference source spelling is an ABI hypothesis.
    CoordStruct &Set_00434820(int x, int y, int z);  // 0x00434820
    // XY-only comparison; name/const spelling are source hypotheses for004BFB60.
    int Equal_XY_004bfb60(CoordStruct const &other) const;
#ifdef RA2_COORD_AS_CELL
    Cell As_Cell() const;  // 0x00413770 out-of-line copy (TibSun Coord::As_Cell)
#endif
#ifndef RA2_COORD_TPOINT3D
    int X;
    int Y;
    int Z;
#endif
};

#ifdef RA2_COORD_PLUS_POINT2D
#include "shared/rect.hpp"
inline CoordStruct const CoordStruct::operator+(Point2D const &point) const
{
    return CoordStruct(X + point.X, Y + point.Y, Z);
}
#endif

// Member-wise coordinate comparison, the free inline form every unit uses
// (formerly defined separately in shared/locomotion.hpp and
// shared/radar.hpp; the locomotors, radar slot 51 and BulletClass
// 0x00461DE0 expand it). The Planning unit instead sees the out-of-line
// member operator== above (RA2_COORD_EQUAL_MEMBER); both forms would make its
// comparisons ambiguous, so the free form is left out there.
#ifndef RA2_COORDSTRUCT_COMPARE
#define RA2_COORDSTRUCT_COMPARE
#ifndef RA2_COORD_EQUAL_MEMBER
inline bool operator==(CoordStruct const &left, CoordStruct const &right)
{
    return left.X == right.X && left.Y == right.Y && left.Z == right.Z;
}
#endif
inline bool operator!=(CoordStruct const &left, CoordStruct const &right)
{
    return left.X != right.X || left.Y != right.Y || left.Z != right.Z;
}
#endif

// A coordinate type derived from CoordStruct whose (x, y, z) constructor only
// forwards to CoordStruct's (name and base are hypotheses). Evidence: two
// out-of-line copies with identical code (three stores, returns this, ret 12):
// 0x0041B630 (190 calls, 108 of them read the returned this to copy a
// temporary: the out-of-line CoordStruct(int, int, int); accepted elsewhere
// as UnknownVector3) and 0x00434820 (17 calls in 9 units, first emitted by
// the BuildingLight unit; accepted alone as CoordStruct::Set_00434820). In
// DynamicVectorClass<WaypointClass>::Resize (0x007256C0) the heap new[]
// loop calls 0x00434820 and the placement new[] loop calls 0x0041B630: the
// placement loop expands one more constructor level, so 0x00434820 wraps
// 0x0041B630 (Study72). WaypointClass (shared/waypoint_path.hpp) holds one.
struct UnknownCoord434820 : CoordStruct {
    UnknownCoord434820() {}
    UnknownCoord434820(int x, int y, int z) : CoordStruct(x, y, z) {}
    UnknownCoord434820(CoordStruct const &coord) { X=coord.X; Y=coord.Y; Z=coord.Z; }
#if defined(RA2_COORD_FROM_CELL) || defined(RA2_COORD_FROM_CELL_INLINE)
    UnknownCoord434820(Cell const &cell, int z = 0);
#endif
};

// Westwood's Cell is TibSun's `Cell : TPoint2D<short>` (coord.h): the
// arithmetic is TPoint2D<short>'s member operators (shared/point.hpp), whose
// TPoint2D<short> results convert back through Cell(BASECLASS const &).
class Cell : public TPoint2D<short> {
    typedef TPoint2D<short> BASECLASS;
public:
    int Not_Equal_0058db50(Cell const &other) const; //fullEAX0/1,thiscall/RET4
    // Original full-EAX comparison at004FEF20; thiscall/RET4.
    int Equal_004fef20(Cell const &other) const;
    void unknown_47e2b0(); // 0047E2B0 empty RET; nonconst/nonvirtual coordinate operation hypothesis
    Cell() {}
    // Original inline conversion, signed division toward zero; source name hypothesis.
    Cell(CoordStruct const &coord) { *this=Cell(coord.X/256,coord.Y/256); }
    // TibSun's int constructor. 0x0042AD30 is the out-of-line copy (two word
    // stores, returns this). The int-to-short conversions make it 41-42 IL
    // units, just over the free line, so /Ob2 charges each expansion against
    // the caller's budget: the Map spread tables (0x005441E0 288 of 369,
    // 0x005461A0 241 of 309, 0x0055B520 8 of 40, 0x0055CBC0 7 of 42) and
    // DynamicVectorClass<ZoneConnectionClass>::Resize (0x0056B330, To out of
    // line) run out exactly as the original does (Study37, Screen40,
    // InlineLab398).
    Cell(int x, int y) : BASECLASS(x, y) {}
    // A TPoint2D<short> result (a sum or difference) taken as a cell.
    Cell(BASECLASS const &pt) : BASECLASS(pt) {}
    Cell &Set(short x, short y) { X = x; Y = y; return *this; }
#ifdef RA2_CELL_AS_COORD
    // TibSun Cell::As_Coord: the centre of the cell at height z, built in a named coordinate
    // (the map preview unit 0x0061D240 reads its Y through it).
    CoordStruct As_Coord(int z = 0) const
    {
        CoordStruct coord(X * 256 + 128, Y * 256 + 128, z);
        return coord;
    }
#endif
#ifdef RA2_COORD_AS_CELL
    // TibSun TPoint2D comparisons (0x0058DB50 is the out-of-line operator!=).
#ifdef RA2_CELL_EQ_RETURNS_INT
    int operator==(Cell const &rvalue) const { return X == rvalue.X && Y == rvalue.Y; }
#else
    bool operator==(Cell const &rvalue) const { return X == rvalue.X && Y == rvalue.Y; }
#endif
    bool operator!=(Cell const &rvalue) const { return X != rvalue.X || Y != rvalue.Y; }
#endif
    bool Unknown_00493C80();   // 0x00493C80 (removes the cell's crate overlay and redraws it; CrateClass)
};

#ifdef RA2_COORD_FROM_CELL_INLINE
#ifdef RA2_COORD_TPOINT3D
#ifdef RA2_COORD_CELL_BASE_INIT
inline CoordStruct::CoordStruct(Cell const &cell, int z)
    : BASECLASS(cell.X * 256 + 128, cell.Y * 256 + 128, z) {}
#else
inline CoordStruct::CoordStruct(Cell const &cell, int z) {
    int x = cell.X * 256 + 128;
    int y = cell.Y * 256 + 128;
    X = x;
    Y = y;
    Z = z;
}
#endif
#else
inline CoordStruct::CoordStruct(Cell const &cell, int z) : X(cell.X * 256 + 128), Y(cell.Y * 256 + 128), Z(z) {}
#endif
inline UnknownCoord434820::UnknownCoord434820(Cell const &cell, int z) : CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, z) {}
#endif

#ifdef RA2_COORD_AS_CELL
inline Cell CoordStruct::As_Cell() const
{
#ifdef RA2_COORD_AS_CELL_NO_CASTS
    return Cell(X / 256, Y / 256);
#else
    return Cell((int)X / 256, (int)Y / 256);
#endif
}
#endif

// The coordinate X, Y, Z (Westwood's XYZ_Coord; hypothesis). Its arguments are a
// call's, evaluated right to left, so Z is computed before Y and X (the TAction
// reveal actions 0x006B0670 and 0x006B0840, 0x006B26D0).
inline CoordStruct XYZ_Coord(int x, int y, int z)
{
    return CoordStruct(x, y, z);
}

// The centre of a cell at ground level (hypothesis: Westwood's Cell_Coord;
// the cell is taken by value).
inline CoordStruct Cell_Center(Cell cell)
{
    return CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
}
// The same from a cell reference (InfantryClass; TeamClass 0x006B91C0 reads a returned cell in place).
inline CoordStruct Cell_Coord(Cell const &cell)
{
    return CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
}

// The cell at X, Y (Westwood's XY_Cell; the original passes int
// coordinates, narrowed only when stored).
inline Cell XY_Cell(int x, int y)
{
    Cell cell;
    cell.X = x;
    cell.Y = y;
    return cell;
}

// The coordinate moved to the corner of its cell (each of X and Y rounded
// toward zero to a multiple of 256; CellClass 0x0047A4E0).
inline CoordStruct Coord_Snap(CoordStruct const &coord)
{
    return UnknownCoord434820(coord.X / 256 * 256, coord.Y / 256 * 256, coord.Z);
}

// Member-wise cell equality (VectorClass<Cell> ID lookups; formerly
// duplicated in shared/map.hpp and shared/house.hpp).
#if !defined(RA2_CELLSTRUCT_COMPARE) && !defined(RA2_COORD_AS_CELL)
#define RA2_CELLSTRUCT_COMPARE
inline bool operator==(Cell const &a, Cell const &b) { return a.X == b.X && a.Y == b.Y; }
inline bool operator!=(Cell const &a, Cell const &b) { return !(a == b); }
#endif


#endif
