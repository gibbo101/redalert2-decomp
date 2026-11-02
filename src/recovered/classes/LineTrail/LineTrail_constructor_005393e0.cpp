// LineTrail constructor: 0x005393E0, complete native body164 bytes +12 NOP.
#include "shared/line_trail.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_l=00a6e948
// @ref ?unknown_LineTrail_list_00a6e970@@3V?$DynamicVectorClass@PAVLineTrail@@@@A=00a6e970

LineTrail::LineTrail() : Color(128,128,128), Owner(0), Decrement(16), ActiveSlot(0)
{
    for (int index=0;index<32;++index) {
        Trails[index].Position=unknown_geometry_l;
        Trails[index].Value=0;
    }
    unknown_LineTrail_list_00a6e970.Add(this);
}
