// int __fastcall VQA_Unknown_0071D660(VQAHandle *handle, int unknown2, int unknown3, int unknown4) (0x0071D660)
// Library callback: forwards to the owning player's 0x0071CA00.
#include "shared/movie.hpp"

int __fastcall VQA_Unknown_0071D660(VQAHandle *handle, int unknown2, int unknown3, int unknown4)
{
    return handle->Player->Unknown_0071CA00(unknown2, unknown3, unknown4);
}
