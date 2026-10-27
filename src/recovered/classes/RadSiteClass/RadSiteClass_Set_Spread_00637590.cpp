// ?Set_Spread@RadSiteClass@@QAEXH@Z (0x00637590)
// Spread in cells and in leptons (cell centre).
#include "shared/radsite.hpp"

void RadSiteClass::Set_Spread(int spread)
{
    Spread = spread;
    SpreadInLeptons = spread * 256 + 128;
}
