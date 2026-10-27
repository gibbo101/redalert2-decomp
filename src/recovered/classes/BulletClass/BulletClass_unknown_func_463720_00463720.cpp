// void BulletClass::unknown_func_463720(Cell cell, int spread, int level) (0x00463720)
// See shared/bullet.hpp: a new radiation site (0x74 bytes) is based at the
// cell with the spread and level and activated (0x00637640), then entered in
// the cell (0x0047CE30); a cell that has one gets the level added.
#include "shared/bullet.hpp"
#include "shared/radsite.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0047CE40@RadSiteCell@@QAEPAVRadSiteClass@@XZ=0047ce40
// @ref ?Unknown_0047CE30@RadSiteCell@@QAEXPAVRadSiteClass@@@Z=0047ce30
// @ref ??0RadSiteClass@@QAE@XZ=006372a0
// @ref ?Set_Base_Cell@RadSiteClass@@QAEXABVCell@@@Z=00637580
// @ref ?Set_Spread@RadSiteClass@@QAEXH@Z=00637590
// @ref ?Set_Rad_Level@RadSiteClass@@QAEXH@Z=006375b0
// @ref ?Unknown_00637640@RadSiteClass@@QAEXXZ=00637640
// @ref ?Increase_Radiation@RadSiteClass@@QAEXH@Z=006375f0
// @ref ??2@YAPAXI@Z=00782017

void BulletClass::unknown_func_463720(Cell cell, int spread, int level)
{
    RadSiteCell &where = (RadSiteCell &)Map[cell];
    RadSiteClass *site = where.Unknown_0047CE40();
    if (site == 0) {
        site = new RadSiteClass();
        site->Set_Base_Cell(cell);
        site->Set_Spread(spread);
        site->Set_Rad_Level(level);
        site->Unknown_00637640();
        where.Unknown_0047CE30(site);
    } else {
        site->Increase_Radiation(level);
    }
}
