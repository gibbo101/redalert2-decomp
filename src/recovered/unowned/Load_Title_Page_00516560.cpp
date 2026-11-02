// void __fastcall Load_Title_Page() -- 0x00516560
#include "shared/cc_file_class.hpp"
#include "shared/palette.hpp"
#include "shared/text_print.hpp"
#include "shared/string_table.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/audio.hpp"
#include "shared/unknown_globals.hpp"

// @ref ??_C@_0BA@NANB@D?3?2Ra2?2Init?4CPP?$AA@=007db8e4
// @ref ??_C@_07ILD@GLS?4PAL?$AA@=007dc024
// @ref ??_C@_08OBPO@GLSS?4SHP?$AA@=007dc018
// @ref ??_C@_08ICHL@GLSL?4SHP?$AA@=007dc00c
// @ref ??_C@_0O@NBN@TXT_COPYRIGHT?$AA@=007dbffc
// @ref ??_C@_0M@BMJG@GUI?3WWBrand?$AA@=007dbff0
// @ref ??_C@_0O@DELH@GUI?3LoadingEx?$AA@=007dbfe0
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ?unknown_title_time_a41668@@3_JA=00a41668

// When the title page was shown plus five seconds (0x00A41668, Audio_Now time).
extern __int64 unknown_title_time_a41668;

// Shows the title shape (GLSS.SHP at 640 wide, else GLSL.SHP, in GLS.PAL) centred on the hidden
// surface with the copyright, brand and loading texts, and blits it (Red Alert's
// Load_Title_Page).
void __fastcall Load_Title_Page()
{
    CCFileClass file("GLS.PAL");
    ShapeFileStruct *shape = 0;
    PaletteClass *palette = 0;
    ConvertClass *drawer = 0;
    if (file.Is_Available()) {
        palette = (PaletteClass *)Load_Alloc_Data(file);
        file.Close();
        for (int index = 0; index < 256; index++) {
            RGBClass &color = (*palette)[index];
            color = RGBClass(color.Red << 2, color.Green << 2, color.Blue << 2);
        }
        if (palette != 0) {
            drawer = new ConvertClass(*palette, unknown_palette_837e10, unknown_surface_839950, 1, false);
            if (drawer != 0) {
                CCFileClass shapefile(unknown_8523e0 == 640 ? "GLSS.SHP" : "GLSL.SHP");
                if (shapefile.Is_Available()) {
                    shape = (ShapeFileStruct *)Load_Alloc_Data(shapefile);
                    shapefile.Close();
                }
            }
        }
    }

    RECT client;
    GetClientRect(MainWindow, &client);
    Rect area(0, 0, client.right - client.left, client.bottom - client.top);
    if (shape != 0) {
        Point2D xy((area.Width - shape->Width) / 2, (area.Height - shape->Height) / 2);
        CC_Draw_Shape(unknown_surface_839954, drawer, shape, 0, xy, area, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
    }

    wchar_t const *text = StringTable::Load_String("TXT_COPYRIGHT", 0, "D:\\Ra2\\Init.CPP", 4700);
    BitFontClass *font = Font_For_Style(0x16);
    Point2D xy(0, area.Height - 60);
    if (font != 0) {
        xy.X = area.Width - font->String_Pixel_Width(text, 0) - 50;
    }
    Plain_Text_Print(text, unknown_surface_839954, &area, &xy, 0xFFFF, 0, 0x16);

    text = StringTable::Load_String("GUI:WWBrand", 0, "D:\\Ra2\\Init.CPP", 4711);
    if (font != 0) {
        xy.X = area.Width - font->String_Pixel_Width(text, 0) - 50;
        xy.Y += font->Height + 3;
    }
    Plain_Text_Print(text, unknown_surface_839954, &area, &xy, 0xFFFF, 0, 0x16);

    text = StringTable::Load_String("GUI:LoadingEx", 0, "D:\\Ra2\\Init.CPP", 4721);
    xy.X = 10;
    xy.Y = 10;
    Plain_Text_Print(text, unknown_surface_839954, &area, &xy, 0xFFFF, 0, 0x16);

    GScreenClass::Blit(true, unknown_surface_839954);
    unknown_title_time_a41668 = Audio_Now() + 5000;
    if (palette != 0) {
        operator delete(palette);
    }
    if (shape != 0) {
        operator delete(shape);
    }
    delete drawer;
}

// @ref ?Audio_Now@@YI_JXZ=004092d0
