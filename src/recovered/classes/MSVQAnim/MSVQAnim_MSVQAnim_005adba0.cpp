// MSVQAnim::MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, Rect const &dest, bool unknown_2c) (0x005ADBA0)
// Opens the movie into `surface` (source centred, destination `dest`) and
// loads "<name up to '.'>.PCX" when present.
#include "shared/ms_anim.hpp"
#include "shared/wstring.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??_7MSVQAnim@@6B@=007a6e04
// @ref ?VQA_Unknown_005A1010@@YIPAVVQAMovie@@PBDPAVSurface@@VRect@@2HH@Z=005a1010
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_volume_a40b44@@3MA=00a40b44
// @ref __real@8@4006ff00000000000000=007a2f50
// @ref __ftol=0077f110

MSVQAnim::MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, Rect const &dest,
                   bool unknown_2c) :
    Movie(0),
    Target(surface),
    Anims(anims),
    Image(0),
    unknown_2c(unknown_2c),
    Done(false)
{
    if (name != 0 && surface != 0) {
        Movie = VQA_Unknown_005A1010(name.Peek_Buffer(), surface, Rect(0, 0, 0, 0), Rect(0, 0, 0, 0),
                                     (int)(unknown_volume_a40b44 * 255.0), 0);
        if (Movie != 0) {
            Movie->Source = Rect((surface->Get_Width() - unknown_8523e0) / 2,
                                 (surface->Get_Height() - unknown_8523e4) / 2, unknown_8523e0, unknown_8523e4);
            Movie->Dest = dest;
        }
        Wstring base;
        name.Get_Token(0, ".", base);
        CCFileClass file(base + ".PCX");
        if (file.Is_Available()) {
            Image = unknown_load_pcx_60d110(&file, 0, 0, 0);
        }
    }
}
