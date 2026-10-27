// bool SidebarClass::Unknown_00681740(int type, int id, UnknownFactory *factory) (0x00681740)
// Passes a finished factory to the strip of its buildable type.
#include "shared/sidebar.hpp"
#include "shared/sidebar_screen.hpp"
// @ref ?Unknown_004EB550@@YIHHH@Z=004eb550
// @ref ?Unknown_006817D0@StripClass@SidebarClass@@QAE_NPAVUnknownFactory@@@Z=006817d0

bool SidebarClass::Unknown_00681740(int type, int id, UnknownFactory *factory)
{
    return Column[Which_Column(type, id)].Unknown_006817D0(factory);
}
