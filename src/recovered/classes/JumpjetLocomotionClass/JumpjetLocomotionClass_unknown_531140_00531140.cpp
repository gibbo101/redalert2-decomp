// int JumpjetLocomotionClass::unknown_531140() (0x00531140)
// The ground height to hold: the cell top under the object (plus the bridge
// height on a bridge cell); with speed (+0x68 above zero) also the cell one
// step ahead in the current facing (+0x50): the higher of the two when the
// ahead cell is higher, else their mean.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/cell.hpp"
#include "shared/infantry.hpp"
// @ref ?unknown_47a290@CellClass@@QBEHXZ=0047a290
// @ref ?unknown_facing_offsets_851ac0@@3QBUUnknownFacingOffset@@B=00851ac0

int JumpjetLocomotionClass::unknown_531140()
{
    CoordStruct coord = LinkedTo->Coord;
    int height = Map[coord].unknown_47a290();
    if (Map[coord].unknown_140 & 0x100) {
        height += unknown_geometry_j;
    }
    if (unknown_68 > 0.0) {
        UnknownFacingOffset const &offset = unknown_facing_offsets_851ac0[Dir_To_8(unknown_50.Current())];
        coord = CoordStruct(coord.X + offset.X, coord.Y + offset.Y, coord.Z);
        int ahead = Map[coord].unknown_47a290();
        if (Map[coord].unknown_140 & 0x100) {
            height += unknown_geometry_j;
        }
        if (ahead > height) {
            return ahead;
        }
        return (height + ahead) / 2;
    }
    return height;
}
