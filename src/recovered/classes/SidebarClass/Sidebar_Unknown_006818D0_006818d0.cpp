// int __fastcall Unknown_006818D0(int type, int id, int arg3) (0x006818D0)
// A buildable type's sidebar column (2 for 0xF/0x10, 3 for 1/2/3/0x28, 1 for 0x1F/0x20/0x39; types 6 and 7 answer
// whether their kind is 5), or -1.
#include "shared/sidebar.hpp"
int __fastcall Unknown_006818D0(int type, int id, int arg3)
{
    if (type == 0xF || type == 0x10) {
        return 2;
    }
    if (type == 1 || type == 0x28 || type == 2 || type == 3) {
        return 3;
    }
    if (type == 6 || type == 7) {
        return Unknown_004EB550(type, id) == 5;
    }
    if (type == 0x39 || type == 0x20 || type == 0x1F) {
        return 1;
    }
    return -1;
}
