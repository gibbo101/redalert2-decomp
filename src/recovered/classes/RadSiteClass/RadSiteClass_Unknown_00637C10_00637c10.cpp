// void RadSiteClass::Unknown_00637C10() (0x00637C10)
// Takes the site's remaining effect off every cell of the spread square: each
// cell's level (Get_Rad_Level_At) scaled by the decay steps left,
// RadTimeLeft / RadLevelDelay + 1, over unknown_50.
#include "shared/radsite.hpp"
#include "shared/coord_distance.hpp"
// @ref ?Unknown_0047CEC0@RadSiteCell@@QAEXN@Z=0047cec0

void RadSiteClass::Unknown_00637C10()
{
    int steps = RadTimeLeft / Rules->RadLevelDelay + 1;
    int xstart = BaseCell.X - Spread;
    int ystart = BaseCell.Y - Spread;
    int xend = xstart + Spread * 2 + 1;
    int yend = ystart + Spread * 2 + 1;
    for (int y = ystart; y < yend; y++) {
        for (int x = xstart; x < xend; x++) {
            Cell cell(x, y);
            double level = Get_Rad_Level_At(cell);
            level = level / unknown_50 * steps;
            RadSiteCell &target = (RadSiteCell &)Map[cell];
            target.Unknown_0047CEC0(level);
        }
    }
}
