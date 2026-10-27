#include "shared/directdraw.hpp"
extern IDirectDrawSurface *primary_ddraw_surface_008523d8;
// @ref ?primary_ddraw_surface_008523d8@@=008523d8
HRESULT __cdecl Wait_For_Surface_Blit_004961d0()
{
    HRESULT result;
    do {
        result=primary_ddraw_surface_008523d8->GetBltStatus(2);
    } while (result!=0 && result!=DDERR_SURFACELOST);
    return result;
}
