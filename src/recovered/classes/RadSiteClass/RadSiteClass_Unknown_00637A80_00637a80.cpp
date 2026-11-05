// RadSiteClass cell radiation update, reconstructed from complete original.
#include "shared/radsite.hpp"
#include "shared/coord_distance.hpp"
// @ref ?Unknown_0047CEA0@RadSiteCell@@QAEXN@Z=0047cea0
void RadSiteClass::Unknown_00637A80()
{
    int xstart = BaseCell.X - Spread;
    int ystart = BaseCell.Y - Spread;
    int xend = xstart + Spread * 2 + 1;
    int yend = ystart + Spread * 2 + 1;
    for (int y = ystart; y < yend; y++) {
        for (int x = xstart; x < xend; x++) {
            Cell cell(x, y);
            double level = Get_Rad_Level_At(cell);
            RadSiteCell &target = (RadSiteCell &)Map[cell];
            target.Unknown_0047CEA0(level);
        }
    }
}
