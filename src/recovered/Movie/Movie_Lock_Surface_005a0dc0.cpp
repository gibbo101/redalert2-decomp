// int __fastcall Movie_Lock_Surface() (0x005A0DC0)
// The VQA player's lock callback (TibSun Movie_Lock_Surface): locks the current movie's frame surface and
// points the player's draw buffer at it (pitch in pixels, height, the source corner); the buffer address.
#include "shared/movie.hpp"
// @ref ?CurrentVQAMovie@@3PAVVQAMovie@@A=00a710ac
// @ref ?Unknown_0071D240@VQAClass@@QAE_NHHHHH@Z=0071d240

int __fastcall Movie_Lock_Surface()
{
    Surface *surface = CurrentVQAMovie->FrameSurface;
    void *buffer = surface->Lock();
    VQAClass *player = CurrentVQAMovie->Player;
    player->Unknown_0071D240(0, surface->Stride() / surface->Bytes_Per_Pixel(), surface->Get_Height(),
                             CurrentVQAMovie->Source.X, CurrentVQAMovie->Source.Y);
    return (int)buffer;
}
