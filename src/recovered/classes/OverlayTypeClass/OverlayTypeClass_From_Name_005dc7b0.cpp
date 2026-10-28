// static int __fastcall OverlayTypeClass::From_Name(char const *name) (0x005DC7B0)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/overlay_type.hpp"
// @ref __stricmp=00781f20

int __fastcall OverlayTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < OverlayTypes.Count(); index++) {
            if (_stricmp(OverlayTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
