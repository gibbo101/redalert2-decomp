// int __fastcall SidebarClass::Unknown_006827F0(int tab) (0x006827F0)
// The gadget id of a strip tab (0-6), or -1.
#include "shared/sidebar.hpp"

int __fastcall SidebarClass::Unknown_006827F0(int tab)
{
    if (tab == 0) {
        return 0x50B;
    }
    if (tab == 1) {
        return 0x50E;
    }
    if (tab == 2) {
        return 0x516;
    }
    if (tab == 3) {
        return 0x51A;
    }
    if (tab == 4) {
        return 0x51B;
    }
    if (tab == 5) {
        return 0x51C;
    }
    return tab == 6 ? 0x51D : -1;
}
