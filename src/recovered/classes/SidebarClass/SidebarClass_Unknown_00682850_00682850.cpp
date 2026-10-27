// int __fastcall SidebarClass::Unknown_00682850(int id) (0x00682850)
// The strip tab (0-6) of a gadget id, or -1 (the inverse of 0x006827F0).
#include "shared/sidebar.hpp"

int __fastcall SidebarClass::Unknown_00682850(int id)
{
    if (id == 0x50B) {
        return 0;
    }
    if (id == 0x50E) {
        return 1;
    }
    if (id == 0x516) {
        return 2;
    }
    if (id == 0x51A) {
        return 3;
    }
    if (id == 0x51B) {
        return 4;
    }
    if (id == 0x51C) {
        return 5;
    }
    return id == 0x51D ? 6 : -1;
}
