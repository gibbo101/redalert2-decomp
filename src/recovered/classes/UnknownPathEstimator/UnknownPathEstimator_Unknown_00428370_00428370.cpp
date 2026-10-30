// UnknownPathEstimator::Unknown_00428370() (0x00428370): the path from the
// search's start to a node.
#include "shared/path_estimator.hpp"
#include "shared/cell.hpp"
#include "shared/crt_memory.hpp"
// @ref ?unknown_path_levels_84c858@@3PAHA=0084c858
// @ref _?path@?1??Unknown_00428370@UnknownPathEstimator@@QAEPAUUnknownPathType@@PAUUnknownPathNode@@PAH@Z@4U3@A=0084c810
// @ref _?$S40@?1??Unknown_00428370@UnknownPathEstimator@@QAEPAUUnknownPathType@@PAUUnknownPathNode@@PAH@Z@4EA=0084e7d4

UnknownPathType *UnknownPathEstimator::Unknown_00428370(UnknownPathNode *node, int *buffer)
{
    static UnknownPathType path;
    path.Cost = node->unknown_08;
    path.Length = node->unknown_0c;
    path.Overlap = 0;
    path.LastOverlap.Set(0, 0);
    path.Command = buffer;
    path.Height = unknown_path_levels_84c858;
    UnknownPathEntry *entry = node->unknown_00;
    UnknownPathEntry *parent = entry->unknown_08;
    for (int index = node->unknown_0c - 2; index >= 0; index--) {
        if (parent) {
            unknown_path_levels_84c858[index] = parent->unknown_04;
            buffer[index] = Unknown_00428320((*entry->unknown_00)->MapCoords, (*parent->unknown_00)->MapCoords);
        }
        entry = entry->unknown_08;
        parent = parent->unknown_08;
    }
    buffer[node->unknown_0c - 1] = -1;
    path.Start = (*entry->unknown_00)->MapCoords;
    if (path.Cost == 0) {
        path.Cost = 1;
    }
    return &path;
}
