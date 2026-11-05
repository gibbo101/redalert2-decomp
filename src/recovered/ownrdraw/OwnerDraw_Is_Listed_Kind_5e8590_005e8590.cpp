#include "shared/win32_api.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Whether kind is one of the listed dialog kinds (0x005E8590).
BOOL __fastcall Is_Listed_Kind_5e8590(int kind)
{
    if (((((((kind != 0x94) && (kind != 0xd8)) && (kind != 0xf5)) &&
                ((kind != 0xe2 && (kind != 0xd5)))) && (kind != 0x101)) &&
            (((((kind != 0x129 && (kind != 0xd7)) &&
                  ((kind != 0xbb && (((kind != 0x100 && (kind != 0xd6)) && (kind != 0x125))))))
                && ((kind != 0x122 && (kind != 0x112)))) && (kind != 0xe7)))) &&
          ((((kind != 0x116 && (kind != 0x11d)) &&
              ((kind != 0x11c && (((kind != 0xfe && (kind != 0x10f)) && (kind != 0x117)))))) &&
            (((kind != 0x114 && (kind != 0xe6)) &&
              ((kind != 0xf3 &&
                (((kind != 0xf4 && (kind != 700)) &&
                  ((kind != 0x10e && ((kind != 0xbc6 && (kind != 0xbc7)))))))))))))) {
        return 0;
    }
    return 1;
}

}
