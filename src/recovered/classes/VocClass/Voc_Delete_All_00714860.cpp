// void Unknown_00714860() (0x00714860)
// Deletes every sound effect type (each leaves the VocClass list) and, when the static sounds have a pool, stops and
// drops them all and frees the pool (Init_Game and Prog_End call it; hypothesis).
#include "shared/voc_static.hpp"
#include "shared/vox_class.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_voc_static_pool_ad0844@@3PAUAudioPool@@A=00ad0844

void Unknown_00714860()
{
    while (unknown_VocClass_list_00ad0818.Count() > 0) {
        delete unknown_VocClass_list_00ad0818[0];
    }
    if (unknown_voc_static_pool_ad0844 != 0) {
        Unknown_00714410();
        Audio_Pool_Destroy(unknown_voc_static_pool_ad0844);
        unknown_voc_static_pool_ad0844 = 0;
    }
}
