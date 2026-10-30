// Remove or destroy the matching laser-fence segments toward a neighboring post.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
#include "shared/anim.hpp"
inline Cell Adjacent_Cell(Cell const &cell, int facing);
// @ref ?Current@FacingClass@@=004b8be0
// @ref ?unknown_4717b0@CellClass@@=004717b0
// @ref ?Unknown_0047F600@@=0047f600
void BuildingClass::unknown_44e260(int facing, bool explode)
{
    if (Type->LaserFencePost) {
        int range = Type->GuardRange.Value >> 8;
        if (range <= 1) range = 1;
        unsigned axis = (unsigned)facing % 4;
        Cell cell = Coord_Cell(Center_Coord());
        for (int index = 0; index < range; ++index) {
            cell = Adjacent_Cell(cell, facing);
            BuildingClass *segment = static_cast<BuildingClass *>(Map[cell].unknown_4717b0());
            if (segment) {
                if (!segment->Type->LaserFence) return;
                if (Owner() != segment->Owner()) return;
                if ((unsigned)(Dir_To_8(segment->unknown_2e0.Current()) & 3) != axis) return;
                if (explode) {
                    Unknown_0047F600(segment->Center_Coord(), segment->Strength, Rules->unknown_c74, 0, 0);
                    segment->unknown_slot86(&segment->Strength, 0, Rules->unknown_c74, 0, true, 1);
                } else {
                    segment->unknown_slot60();
                }
            }
        }
    }
}
