// int CellClass::unknown_475fe0(int damage) (0x00475FE0): TibSun Reduce_Wall.
// Damages the cell's wall overlay (-1: destroy it outright); a wall that
// reaches its last damage stage takes its same-type neighbours down a stage,
// and a destroyed wall loses its overlay and owner, updates the zones, the
// radar and the neighbouring walls, detaches the cell and lowers the
// neighbours' adjacent counts. Answers whether the wall was destroyed.
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/overlay_type.hpp"
#include "shared/tactical.hpp"
#include "shared/abstract.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"

int CellClass::unknown_475fe0(int damage)
{
    if (OverlayIndex != -1) {
        bool destroyed;
        OverlayTypeClass const *wall = OverlayTypes[OverlayIndex];
        if (wall->Wall) {
            if (damage == -1 || damage >= wall->Strength || unknown_a40774) {
                destroyed = true;
            } else {
                destroyed = Random_Pick(0, wall->Strength) < damage;
            }

            if (destroyed) {
                Rect rect = Union(unknown_474eb0(), unknown_475100());
                rect.Y -= unknown_rect_839630.Y;
                unknown_tactical_83996c->Register_Dirty_Area(rect, false);
                OverlayData += 0x10;
                if ((OverlayData >> 4) == wall->DamageLevels - 1 && wall->DamageLevels > 2) {
                    for (int dir = 0; dir < 8; dir += 2) {
                        CellClass *adjacent = (CellClass *)&((CellClass const *)this)->Adjacent_Cell(dir);
                        if (adjacent->OverlayIndex != -1 && OverlayTypes[adjacent->OverlayIndex]->Wall && adjacent->OverlayIndex == OverlayIndex && adjacent->OverlayData < 0x10) {
                            adjacent->unknown_475fe0(200);
                        }
                    }
                }
                if (damage == -1
                    || (OverlayData >> 4) >= wall->DamageLevels
                    || ((OverlayData >> 4) == wall->DamageLevels - 1 && (OverlayData & 0x0F) == 0)) {
                    unknown_50 = -1;
                    OverlayIndex = -1;
                    OverlayData = 0;
                    Unknown_00472540(-1);
                    Map.Unknown_0054FB20(MapCoords);
                    Map.Unknown_00566340(MapCoords);
                    Map.Unknown_00631570(MapCoords);
                    ((CellClass &)((CellClass const *)this)->Adjacent_Cell(0)).unknown_475960(false);
                    ((CellClass &)((CellClass const *)this)->Adjacent_Cell(6)).unknown_475960(false);
                    ((CellClass &)((CellClass const *)this)->Adjacent_Cell(4)).unknown_475960(false);
                    Adjacent_Cell(2).unknown_475960(false);
                    Unknown_006ECB90(this, true);
                    for (int facing = 0; facing < 8; facing++) {
                        Adjacent_Cell(facing).unknown_122--;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}
