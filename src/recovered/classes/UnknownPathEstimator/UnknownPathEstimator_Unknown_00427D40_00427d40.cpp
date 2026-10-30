// UnknownPathEstimator::Unknown_00427D40() (0x00427D40): takes the next search node for a cell.
#include "shared/path_estimator.hpp"
#include "shared/cell.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"

UnknownPathNode *UnknownPathEstimator::Unknown_00427D40(UnknownPathNode *parent, CellClass **cell, Cell const &target, float cost)
{
    UnknownPathNode *node = &unknown_10->nodes[unknown_10->count++];
    UnknownPathEntry *entry = &unknown_0c->entries[unknown_0c->count++];
    entry->unknown_00 = cell;
    if (parent) {
        entry->unknown_08 = parent->unknown_00;
        CellClass *here = *cell;
        CellClass *from = *parent->unknown_00->unknown_00;
        entry->unknown_04 = here->unknown_11b;
        if (here->unknown_140 & 0x100) {
                        if ((from->unknown_140 & 0x100) && parent->unknown_00->unknown_04 == from->unknown_11b + 4) {
                entry->unknown_04 += 4;
            } else if (!(from->unknown_140 & 0x100) && abs(here->unknown_11b - parent->unknown_00->unknown_04 + 3) <= 1) {
                entry->unknown_04 += 4;
            }
        }
    } else {
        entry->unknown_08 = 0;
        entry->unknown_04 = *(int *)unknown_30;
    }
    node->unknown_00 = entry;
    if (parent) {
        node->unknown_04 = cost + parent->unknown_04;
        node->unknown_0c = parent->unknown_0c + 1;
    } else {
        node->unknown_04 = 0;
        node->unknown_0c = 1;
    }
    Cell const &coords = (*cell)->MapCoords;
    int dx = abs(coords.X - target.X);
    int dy = abs(coords.Y - target.Y);
    node->unknown_08 = Fast_Sqrt(dx * dx + dy * dy) + node->unknown_04;
    return node;
}
