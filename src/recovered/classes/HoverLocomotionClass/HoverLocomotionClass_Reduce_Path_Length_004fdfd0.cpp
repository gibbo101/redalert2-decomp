// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref __ftol=0077f110
#include "shared/hover_locomotion.hpp"
inline int Hover_Distance_004fdfd0(CoordStruct const &from,CoordStruct const &to)
{
    CoordStruct difference=from-to;
    return (int)Fast_Sqrt((double)difference.X*difference.X+(double)difference.Y*difference.Y+(double)difference.Z*difference.Z);
}
bool HoverLocomotionClass::Reduce_Path_Length_004fdfd0()
{
    if (Is_Moving() && LinkedTo->Path[0]!=-1) {
        if ((LinkedTo->unknown_494 && LinkedTo->unknown_494->Kind_Of()==1) ||
            (LinkedTo->unknown_494 && LinkedTo->unknown_494->Kind_Of()==15)) {
            int distance=Hover_Distance_004fdfd0(LinkedTo->Center_Coord(),unknown_18)/256;
            if (distance<24) { LinkedTo->Path[distance]=-1; return true; }
        }
        if (LinkedTo->unknown_228 && LinkedTo->unknown_slot213(LinkedTo->unknown_228)) {
            LinkedTo->Path[0]=-1;
            return true;
        }
    }
    return false;
}
