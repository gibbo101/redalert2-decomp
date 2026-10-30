#include "shared/map_region.hpp"
// Six qword fields initialized to floating zero; constructor/type intent is a hypothesis.
UnknownMapGenerationCell::UnknownMapGenerationCell()
    : Position(0,0), unknown_08(0.0), unknown_10(0.0), unknown_18(0.0),
      unknown_20(0.0), unknown_28(0.0), unknown_30(0.0), RegionIndex(0),
      unknown_3c(0), unknown_40(-1), Marked(0)
{
    unknown_45[0] = 0;
    unknown_45[1] = 0;
    unknown_45[2] = 0;
    unknown_45[3] = 0;
    unknown_45[4] = 0;
    unknown_45[5] = 1;
    unknown_4b = 0;
}
