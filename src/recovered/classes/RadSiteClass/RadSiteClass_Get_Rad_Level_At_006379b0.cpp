// double RadSiteClass::Get_Rad_Level_At(Cell const &cell) (0x006379B0)
// The site's level at a cell: falls off linearly from the base cell to 0 at
// the spread's edge (leptons); 0 outside it.
#include "shared/radsite.hpp"
#include "shared/coord_distance.hpp"

double RadSiteClass::Get_Rad_Level_At(Cell const &cell)
{
    RadSiteCell &base = (RadSiteCell &)Map[BaseCell];
    RadSiteCell &target = (RadSiteCell &)Map[cell];
    CoordStruct base_coord = base.Center_Coord();
    CoordStruct target_coord = target.Center_Coord();
    int distance = Coord_Distance(base_coord, target_coord);
    double level = 0.0;
    if (distance <= SpreadInLeptons) {
        level = (double)(SpreadInLeptons - distance) / SpreadInLeptons * RadLevel;
    }
    return level;
}
