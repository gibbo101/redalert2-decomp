// WDTTerritory::WDTTerritory() (0x0072BE00): the default battle settings (10 units, tech level
// 10, two players, eight 0/100/50 byte triples from +0x1F with the one at +0x2B enabled, no
// option flags chosen). The bytes from +0x15 keep the shared header's unknown_15 view (the map
// seed reads +0x1C-+0x24 through it, MapSeedClass::Apply_WDT_Territory 0x00578BC0).
// @ref ??_7WDTTerritory@@6B@=007af2d8
#include "shared/wdt_territory.hpp"

WDTTerritory::WDTTerritory()
{
    unknown_08 = 0;
    UnitCount = 10;
    TechLevel = 10;
    unknown_10 = 10000;
    *(unsigned short *)unknown_0c = 0;
    unknown_12 = 1;
    unknown_13 = 1;
    PlayerCount = 2;
    unknown_15[0x1C - 0x15] = 1;
    unknown_15[0x1D - 0x15] = 0;
    unknown_15[0x1E - 0x15] = 0;
    unknown_15[0x1F - 0x15] = 0;
    unknown_15[0x20 - 0x15] = 100;
    unknown_15[0x21 - 0x15] = 50;
    unknown_15[0x22 - 0x15] = 0;
    unknown_15[0x23 - 0x15] = 100;
    unknown_15[0x24 - 0x15] = 50;
    unknown_15[0x25 - 0x15] = 0;
    unknown_15[0x26 - 0x15] = 100;
    unknown_15[0x27 - 0x15] = 50;
    unknown_15[0x28 - 0x15] = 0;
    unknown_15[0x29 - 0x15] = 100;
    unknown_15[0x2A - 0x15] = 50;
    unknown_15[0x2B - 0x15] = 1;
    unknown_15[0x2C - 0x15] = 100;
    unknown_15[0x2D - 0x15] = 50;
    unknown_15[0x2E - 0x15] = 0;
    unknown_15[0x2F - 0x15] = 100;
    unknown_15[0x30 - 0x15] = 50;
    unknown_15[0x31 - 0x15] = 0;
    unknown_15[0x32 - 0x15] = 100;
    unknown_15[0x33 - 0x15] = 50;
    unknown_15[0x34 - 0x15] = 0;
    unknown_15[0x35 - 0x15] = 100;
    unknown_15[0x36 - 0x15] = 50;
    OptionFlags = -1;
    unknown_3c = -1;
}
