// int __cdecl VQA_Unknown_0071D6E0(VQAHandle *handle, int event, int unknown3, int unknown4) (0x0071D6E0)
// Library event callback: 2 a new palette (6-bit components scaled by 4),
// 3 frame timing (0x0071D2C0), 6 and 7 the player's callbacks.
#include "shared/movie.hpp"
#include "shared/crt_memory.hpp"

int __cdecl VQA_Unknown_0071D6E0(VQAHandle *handle, int event, int unknown3, int unknown4)
{
    VQAClass *player = handle->Player;
    switch (event) {
    case 2: {
        unsigned char *palette = (unsigned char *)unknown3;
        for (int index = 0; index < 256; index++) {
            palette[index] <<= 2;
        }
        memcpy(player->Palette, palette, sizeof(player->Palette));
        player->PaletteChanged = true;
        return 0;
    }
    case 3:
        player->Unknown_0071D2C0(unknown3, unknown4);
        return 0;
    case 4:
    case 5:
        break;
    case 6:
        return player->Callback538();
    case 7:
        player->Callback53C();
        break;
    }
    return 0;
}
