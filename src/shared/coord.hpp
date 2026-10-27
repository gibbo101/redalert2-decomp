// Map coordinates: CoordStruct (leptons, x/y/z) and Cell (cell x/y).
// Layouts from AbstractClass/ObjectClass (Center_Coord returns a
// CoordStruct) and the per-unit zero constants of
// shared/unknown_geometry.hpp. Names follow Westwood's TS/RA2 vocabulary.
#ifndef RA2_SHARED_COORD_HPP
#define RA2_SHARED_COORD_HPP

struct INIPoint3D;

struct CoordStruct {
    CoordStruct() {}
    CoordStruct(int x, int y, int z) : X(x), Y(y), Z(z) {}
    // From the point an INI reader returns (defined in shared/ini_class.hpp).
    CoordStruct(INIPoint3D const &point);
    // Member-wise difference (0x004348F0 is the out-of-line copy the BuildingLight unit keeps).
    CoordStruct operator-(CoordStruct const &coord) const
    {
        return CoordStruct(X - coord.X, Y - coord.Y, Z - coord.Z);
    }
    // Member-wise sum (AnimClass::Center_Coord, 0x00420D90).
    CoordStruct operator+(CoordStruct const &coord) const
    {
        return CoordStruct(X + coord.X, Y + coord.Y, Z + coord.Z);
    }
#ifdef RA2_COORD_EQUAL_MEMBER
    // Member-wise comparison (0x0061A8B0): the original has a real out-of-line
    // int-returning thiscall member that Planning.cpp calls, while the
    // locomotors use an inline free bool comparison (shared/locomotion.hpp);
    // the two forms coexisted in different translation units. Only the
    // Planning unit defines RA2_COORD_EQUAL_MEMBER (first line of its first
    // draft), so no other unit sees this declaration.
    int operator==(CoordStruct const &coord) const;
#endif
    // Member-wise quotient (0x006D9770 is the Techno unit's out-of-line copy); a zero divisor gives (0, 0, 0).
    CoordStruct operator/(int divisor) const;  // 0x006D9770
    // EAX=this/ret12; returned-reference source spelling is an ABI hypothesis.
    CoordStruct &Set_00434820(int x, int y, int z);  // 0x00434820
    // XY-only comparison; name/const spelling are source hypotheses for004BFB60.
    int Equal_XY_004bfb60(CoordStruct const &other) const;
    int X;
    int Y;
    int Z;
};

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

class Cell {
public:
    void unknown_47e2b0(); // 0047E2B0 empty RET; nonconst/nonvirtual coordinate operation hypothesis
    Cell() {}
    // Stores the coordinates through Set. 0x0042AD30 is the out-of-line copy
    // (two word stores, returns this). The discarded reference Set returns
    // makes the constructor one IL node larger than two plain stores, so /Ob2
    // charges each expansion against the caller's budget instead of expanding
    // it for free: the Map spread tables (0x005441E0 288 of 369, 0x005461A0
    // 241 of 309, 0x0055B520 8 of 40, 0x0055CBC0 7 of 42) and
    // DynamicVectorClass<ZoneConnectionClass>::Resize (0x0056B330, To out of
    // line) run out exactly as the original does (Study37, Screen40). The
    // parameters are short like the members: with int parameters FootClass
    // 0x004CB8F0 loads one operand in the other order (TechFoot39).
    Cell(short x, short y) { Set(x, y); }
    Cell &Set(short x, short y) { X = x; Y = y; return *this; }
    short X;
    short Y;
};

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
    return CoordStruct(coord.X / 256 * 256, coord.Y / 256 * 256, coord.Z);
}

// Member-wise cell equality (VectorClass<Cell> ID lookups; formerly
// duplicated in shared/map.hpp and shared/house.hpp).
#ifndef RA2_CELLSTRUCT_COMPARE
#define RA2_CELLSTRUCT_COMPARE
inline bool operator==(Cell const &a, Cell const &b) { return a.X == b.X && a.Y == b.Y; }
inline bool operator!=(Cell const &a, Cell const &b) { return !(a == b); }
#endif

// Member-wise sum of two cells (formerly one guarded copy each in
// shared/cell.hpp, shared/display.hpp, shared/foot.hpp and shared/terrain.hpp).
#ifndef RA2_CELLSTRUCT_PLUS
#define RA2_CELLSTRUCT_PLUS
inline Cell operator+(Cell const &left, Cell const &right)
{
    return Cell(left.X + right.X, left.Y + right.Y);
}
#endif

#endif
