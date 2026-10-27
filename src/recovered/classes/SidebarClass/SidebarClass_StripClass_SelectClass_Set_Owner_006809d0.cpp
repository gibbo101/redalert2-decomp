// void SidebarClass::StripClass::SelectClass::Set_Owner(StripClass &strip, int index) (0x006809D0)
#include "shared/sidebar.hpp"

void SidebarClass::StripClass::SelectClass::Set_Owner(StripClass &strip, int index)
{
    Strip = &strip;
    Index = index;
}
