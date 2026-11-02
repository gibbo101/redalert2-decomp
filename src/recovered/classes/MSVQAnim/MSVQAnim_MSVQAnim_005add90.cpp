// MSVQAnim::MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, bool unknown_2c) (0x005ADD90)
// As 0x005ADBA0 for a 640x400 movie centred in `surface` and on the screen.
#include "shared/ms_anim.hpp"
#include "shared/wstring.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/dsurface.hpp"
// @ref ?unknown_surface_839954@@3PAVSurface@@A=00839954

MSVQAnim::MSVQAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, bool unknown_2c) :
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
            Movie->Source = Rect((surface->Get_Width() - 640) / 2, (surface->Get_Height() - 400) / 2, 640, 400);
            Movie->Dest = Rect((unknown_surface_839954->Get_Width() - 640) / 2,
                               (unknown_surface_839954->Get_Height() - 400) / 2, 640, 400);
        }
        Wstring base;
        name.Get_Token(0, ".", base);
        CCFileClass file(base + ".PCX");
        if (file.Is_Available()) {
            Image = unknown_load_pcx_60d110(&file, 0, 0, 0);
        }
    }
}
