// int __cdecl VQA_Unknown_0071D490(VQAHandle *handle, int unknown2, int unknown3, int unknown4) (0x0071D490)
// Library stream callback: forwards to the owning player's 0x0071D340.
#include "shared/movie.hpp"
// @ref ?Unknown_0071D340@VQAClass@@QAEHHHH@Z=0071d340

int __cdecl VQA_Unknown_0071D490(VQAHandle *handle, int unknown2, int unknown3, int unknown4)
{
    VQAClass *player = handle->Player;
    return player->Unknown_0071D340(unknown2, unknown3, unknown4);
}
