// Cell FootClass::unknown_4cb8f0(int radius, bool arg2) (0x004CB8F0)
// A cell to dock at: the unit's own cell when its land type is 5;
// otherwise, ring by ring out to the radius, the best-scoring cell
// (0x0047A230) that passes 0x004CB6D0 on the first ring with one (the zero
// cell when none does).
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0047A230@UnknownCellClass@@QAEHXZ=0047a230

Cell FootClass::unknown_4cb8f0(int radius, bool arg2)
{
    Cell found = unknown_geometry_k;
    Cell center = Center_Coord();
    if (((UnknownCellClass *)&Map[center])->unknown_ec == 5) {
        return center;
    }
    int best = -1;
    for (int ring = 1; ring < radius; ring++) {
        for (int index = -ring; index <= ring; index++) {
            Cell cell = center + Cell(index, -ring);
            if (unknown_4cb6d0(cell)) {
                int score = ((UnknownCellClass *)&Map[cell])->Unknown_0047A230();
                if (score > best) {
                    best = score;
                    found = cell;
                }
            }
            cell = center + Cell(index, ring);
            if (unknown_4cb6d0(cell)) {
                int score = ((UnknownCellClass *)&Map[cell])->Unknown_0047A230();
                if (score > best) {
                    best = score;
                    found = cell;
                }
            }
            cell = center + Cell(-ring, index);
            if (unknown_4cb6d0(cell)) {
                int score = ((UnknownCellClass *)&Map[cell])->Unknown_0047A230();
                if (score > best) {
                    best = score;
                    found = cell;
                }
            }
            cell = center + Cell(ring, index);
            if (unknown_4cb6d0(cell)) {
                int score = ((UnknownCellClass *)&Map[cell])->Unknown_0047A230();
                if (score > best) {
                    best = score;
                    found = cell;
                }
            }
        }
        if (best != -1) {
            break;
        }
    }
    return found;
}
