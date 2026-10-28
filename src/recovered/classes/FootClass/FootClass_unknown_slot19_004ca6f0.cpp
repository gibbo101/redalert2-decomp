// CoordStruct FootClass::unknown_slot19(TechnoClass *techno) const (0x004CA6F0)
// Inside a tube (+0x574 set): the centre of its cell; otherwise where the
// locomotor is heading (ILocomotion::Head_To_Coord), or the object's own
// coordinate when that is the zero coordinate.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAUUnknownTube@@@@A=008661c8

CoordStruct FootClass::unknown_slot19(TechnoClass *techno) const
{
    if (unknown_574 >= 0) {
        Cell cell = unknown_TubeClass_list_008661c8[unknown_574]->ExitCell;
        return CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0);
    }
    CoordStruct coord = Locomotor.Checked()->Head_To_Coord();
    if (coord != unknown_geometry_l) {
        return coord;
    }
    return Center_Coord();
}
