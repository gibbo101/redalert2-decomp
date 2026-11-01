// Derive a path start after the already queued steps and ask the shared estimator.
#include "shared/foot.hpp"
UnknownPathType *FootClass::Unknown_004BB350(Cell *dest,int *moves,int maximum,int threshold,int path_offset,int avoidance)
{
    Cell source=Cell(unknown_slot19(0));
    if (!moves) return 0;
    source=UnknownPathEstimator::Unknown_00427060(source,path_offset,Path);
    return unknown_path_estimator_8315c8.Find_Path_0042a1d0(source,*dest,this,moves,-1,-1,avoidance);
}
