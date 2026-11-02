// Loads a title picture, redraws its background and draws the paletted/image surface.
#include "shared/win_stub.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/surface.hpp"
#include "shared/convert.hpp"
#include "shared/surface_blit.hpp"
Surface *__fastcall unknown_load_pcx_60d110(FileClass *file, PaletteClass *palette, int unknown3, int unknown4);
void __fastcall Unknown_006F3A20(Surface *surface, Rect const &window, bool draw);
Rect __fastcall Unknown_006F1F30();
extern int const title_width_threshold_007add70;
void __fastcall Load_Title_Screen_00738190(char const *name, Surface *surface, PaletteClass *palette)
{
    CCFileClass file(name);
    Surface *image = unknown_load_pcx_60d110(&file, palette, 0, 0);
    if (image) {
        int width = surface->Get_Width();
        int height = surface->Get_Height();
        Rect background_rect(0, 0, width, height);
        BSurface *background = new BSurface(width, height, 2);
        Unknown_006F3A20(background, background_rect, false);
        surface->Copy_From(*background, false, true);
        delete background;
        int x = 0;
        int y = 0;
        int image_width = image->Get_Width();
        int image_height = image->Get_Height();
        if (surface->Get_Width() > title_width_threshold_007add70) {
            Rect window = Unknown_006F1F30();
            x = (window.Width - image_width) / 2;
            y = (window.Height - image_height) / 2;
        }
        if (palette && image->Bytes_Per_Pixel() == 1) {
            ConvertClass *convert = new ConvertClass(*palette, *palette, surface, 1, false);
            unknown_blit_49f3a0(*surface, convert, *image, image->Get_Rect(),
                RectPoint2D(x, y), surface->Get_Rect(), 0, 0, 0, 0, 1000, 0);
            delete convert;
        } else {
            surface->Copy_From(surface->Get_Rect(), Rect(x, y, image->Get_Width(), image->Get_Height()),
                *image, image->Get_Rect(), image->Get_Rect(), false, true);
        }
        delete image;
    }
}
// @ref ?unknown_load_pcx_60d110@@YIPAVSurface@@PAVFileClass@@PAVPaletteClass@@HH@Z=0060d110
// @ref ?Unknown_006F3A20@@YIXPAVSurface@@ABVRect@@_N@Z=006f3a20
// @ref ?Unknown_006F1F30@@YI?AVRect@@XZ=006f1f30
// @ref ?title_width_threshold_007add70@@3HB=007add70
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??0ConvertClass@@QAE@ABVPaletteClass@@0PAVSurface@@H_N@Z=00483650
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??2@YAPAXI@Z=00782017
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ?unknown_blit_49f3a0@@YIXAAVSurface@@PAX0ABVRect@@ABURectPoint2D@@2HHHHHH@Z=0049f3a0
