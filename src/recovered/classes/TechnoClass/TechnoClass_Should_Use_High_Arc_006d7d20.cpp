// Whether the selected weapon must lob over a steep rise to its target.
#include "shared/techno.hpp"
#include "shared/weapon_type.hpp"
#include "shared/fast_math.hpp"
// The existing Point2D length implementation, visible inline in this caller;
// any emitted original copy must still pass complete kept-elsewhere closure.
// @ref ?Length@Point2D@@QBEHXZ=0047d060
inline int Point2D::Length() const
{
    return (int)Fast_Sqrt((double)X*X+(double)Y*Y);
}

bool TechnoClass::unknown_6d7d20(int weapon)
{
    WeaponTypeClass *type=unknown_slot231(weapon)->WeaponType;
    if(!type) return true;
    bool high_arc=type->unknown_10a;
    if(!high_arc && unknown_228) {
        int height=unknown_228->Center_Coord().Z-Position_Coord_004f3f40().Z;
        if(height>0) {
            // CoordStruct's first two signed32-bit fields are the XY point
            // prefix (reference Coord inherits the point); this storage view
            // keeps the existing shared Point2D constructor/API unchanged.
            if((Point2D(reinterpret_cast<RectPoint2D const &>(static_cast<CoordStruct const &>(Position_Coord_004f3f40())))-Point2D(reinterpret_cast<RectPoint2D const &>(static_cast<CoordStruct const &>(unknown_228->Center_Coord())))).Length()<height) high_arc=true;
        }
    }
    return high_arc;
}
