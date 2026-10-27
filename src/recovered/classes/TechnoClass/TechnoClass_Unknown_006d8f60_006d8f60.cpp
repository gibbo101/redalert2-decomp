// int __fastcall Unknown_006D8F60(int kind, int unused_edx, int unused_stack) (0x006D8F60)
// Maps kind 1 to 0x3E and kind 5 to 0x3F while 0x006F6670 holds; other kinds pass through.
#include "shared/techno.hpp"
// @ref ?Unknown_006F6670@@YA_NXZ=006f6670

bool Unknown_006F6670();

int __fastcall Unknown_006D8F60(int kind, int unused_edx, int unused_stack)
{
    bool pressed = Unknown_006F6670();
    if (kind == 1) {
        if (pressed) {
            return 0x3E;
        }
    } else if (kind == 5 && pressed) {
        return 0x3F;
    }
    return kind;
}
