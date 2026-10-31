// Start an infantry move at a free subcell and transfer its occupancy reservation.
#include "shared/infantry.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/unknown_geometry.hpp"
extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;
extern double const unknown_facing_radians_79b620;
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);
// @ref ?unknown_facing_scale_79b628@@3NB=0079b628
// @ref ?unknown_facing_origin_79b630@@3NB=0079b630
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref __real@8@4005f800000000000000=007a3a28
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?unknown_slot290@FootClass@@=004c4b90
// @ref ?Unknown_004764B0@UnknownCellClass@@=004764b0
inline double UnknownFacingDir::As_Radian() const
{
    return (short(Raw)-0x3fff)*unknown_facing_radians_79b620;
}
// Inline direction operations; member-versus-free spelling is unproved for RA2.
inline UnknownFacingDir Direction_00504bc0(CoordStruct const &from, CoordStruct const &to)
{
    UnknownFacingDir direction;
    if (from.Equal_XY_004bfb60(to)) direction.Raw=0;
    direction=UnknownFacingDir((unsigned short)(int)((Fast_Atan2(double(from.Y)-to.Y,double(to.X)-from.X)-unknown_facing_origin_79b630)*unknown_facing_scale_79b628));
    return direction;
}
inline UnknownFacingDir operator+(UnknownFacingDir const &left, UnknownFacingDir const &right)
{
    return UnknownFacingDir(left.Raw+right.Raw);
}
// A view of the evidenced four-byte cell flags; bridge is bit 8.
struct CellBridgeFlags_00504bc0 {
    unsigned unknown_low : 8;
    unsigned under_bridge : 1;
    unsigned unknown_high : 23;
};
inline CoordStruct Move_Coord(CoordStruct const &start, UnknownFacingDir const &direction, int distance)
{
    double angle=direction.As_Radian();
    return CoordStruct(int(start.X+unknown_cos_4ba4d0(angle)*distance),int(start.Y-unknown_sin_4ba480(angle)*distance),start.Z);
}
bool InfantryClass::unknown_slot290(CoordStruct &headto)
{
    CoordStruct old=headto;
    headto=reinterpret_cast<UnknownCellClass &>(Map[headto]).Unknown_004764B0(Move_Coord(headto,Direction_00504bc0(Center_Coord(),headto)+UnknownFacingDir(0x7fff),124),false,reinterpret_cast<CellBridgeFlags_00504bc0 const &>(Map[headto].unknown_140).under_bridge);
    if (headto==unknown_geometry_l && unknown_slot101(&Map[old],-1,-1,0,1)==0) {
        headto=reinterpret_cast<UnknownCellClass &>(Map[old]).Unknown_004764B0(Move_Coord(old,Direction_00504bc0(Center_Coord(),headto)+UnknownFacingDir(0x7fff),128),true,reinterpret_cast<CellBridgeFlags_00504bc0 const &>(Map[old].unknown_140).under_bridge);
    }
    if (headto!=unknown_geometry_l && FootClass::unknown_slot290(headto)) {
        if (!unknown_7d) return false;
        unknown_slot59(CoordStruct(Coord));
        unknown_slot58(headto);
        return true;
    }
    return false;
}
