// int __cdecl VQA_Unknown_0071D680(VQAHandle *handle, int request, int unknown3, int unknown4) (0x0071D680)
// Library memory callback: 2 allocates unknown4 bytes, 3 frees unknown3,
// 4 and 5 return unknown3, 6 stores -1 through it.
#include "shared/movie.hpp"
// @ref _malloc=00782630
// @ref _free=007825e8

extern "C" void *__cdecl malloc(unsigned size);
extern "C" void __cdecl free(void *block);

int __cdecl VQA_Unknown_0071D680(VQAHandle *handle, int request, int unknown3, int unknown4)
{
    switch (request) {
    case 2:
        return (int)malloc(unknown4);
    case 3:
        free((void *)unknown3);
        return 0;
    case 4:
    case 5:
        return unknown3;
    case 6:
        *(int *)unknown3 = -1;
        break;
    }
    return 0;
}
