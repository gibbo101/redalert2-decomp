// void CellClass::unknown_47c930() (0x0047C930): TibSun's On_Bridge_Collapse:
// when the cell carries bridge occupants, every moving foot object in the
// surrounding 5x5 cells whose locomotor is heading for the bridge deck
// (Is_Moving_Here) is destroyed with the C4 warhead. Height from Map, plus the bridge deck height.
#include "shared/cell.hpp"
#include "shared/display.hpp"
#include "shared/map_view.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848

void CellClass::unknown_47c930()
{
    if (unknown_128) {
        CoordStruct coord = MapCoords.As_Coord();
        coord.Z = Map.Unknown_0055A280(coord) + unknown_geometry_j;
        for (int x = -2; x < 3; x++) {
            for (int y = -2; y < 3; y++) {
                Cell cell = MapCoords + Cell(x, y);
                CellClass *cellptr = &Map[cell];
                if (cellptr != this) {
                    ObjectClass *optr = 0;
                    ObjectClass *next = 0;
                    optr = cellptr->AltOccupierPtr;
                    while (optr != 0) {
                        next = optr->unknown_30;
                        bool is_foot;
                        if (optr != 0) {
                            is_foot = optr->AbstractFlags.IsFoot;
                        }
                        if (optr != 0 && is_foot) {
                            FootClass *fptr = (FootClass *)optr;
                            if (fptr->Locomotor.Checked()->Is_Moving_Here(coord)) {
                                int damage = fptr->Strength;
                                fptr->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, true);
                            }
                        }
                        optr = next;
                    }
                    optr = cellptr->OccupierPtr;
                    while (optr != 0) {
                        next = optr->unknown_30;
                        bool is_foot;
                        if (optr != 0) {
                            is_foot = optr->AbstractFlags.IsFoot;
                        }
                        if (optr != 0 && is_foot) {
                            FootClass *fptr = (FootClass *)optr;
                            if (fptr->Locomotor.Checked()->Is_Moving_Here(coord)) {
                                int damage = fptr->Strength;
                                fptr->unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, true);
                            }
                        }
                        optr = next;
                    }
                }
            }
        }
    }
}
