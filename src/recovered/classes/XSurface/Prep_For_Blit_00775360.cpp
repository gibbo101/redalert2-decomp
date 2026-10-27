// bool __fastcall Prep_For_Blit(Surface &dest, Rect &drect, Surface &source, Rect &srect, bool &overlapped, void *&dbuffer, void *&sbuffer) (0x00775360)
// Prepares a blit clipped to the two surfaces' own rectangles.
#include "shared/surface.hpp"
// @ref ?Prep_For_Blit@@YI_NAAVSurface@@ABVRect@@AAV2@012AA_NAAPAX4@Z=007753b0

bool __fastcall Prep_For_Blit(Surface &dest, Rect &drect, Surface &source, Rect &srect, bool &overlapped,
                              void *&dbuffer, void *&sbuffer)
{
    return Prep_For_Blit(dest, dest.Get_Rect(), drect, source, source.Get_Rect(), srect, overlapped, dbuffer,
                         sbuffer);
}
