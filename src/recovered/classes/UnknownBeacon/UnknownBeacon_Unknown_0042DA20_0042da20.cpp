#define SHAPE_FILE_EMPTY_RECT Rect(0, 0, 0, 0)
#include "shared/beacon.hpp"
#include "shared/house.hpp"
#include "shared/tactical.hpp"
#include "shared/text_print.hpp"
#include "shared/palette.hpp"
#include "shared/cd_timer.hpp"
#include "shared/keyboard.hpp"
// @ref ?Print_Box@BitTextClass@@QAEHPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?unknown_beacon_cycle_84e93c@@3HA=0084e93c
// @ref ?unknown_flag_a3dc89@@3_NA=00a3dc89
// @ref _wcsrchr=007835c5

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" unsigned int __cdecl wcslen(unsigned short const *string);
extern "C" unsigned short *__cdecl wcsrchr(unsigned short const *string, unsigned short character);   // 0x007835C5

void UnknownBeacon::Unknown_0042DA20(Surface *surface, Rect rect)
{
    ColorScheme *scheme = ColorSchemes[Houses[unknown_house]->ColorSchemeIndex];
    Point2D pixel;
    if (!unknown_tactical_83996c->Unknown_006A29D0(unknown_coord, pixel)) {
        return;
    }
    int half = unknown_beacon_cycle_84e93c / 2;
    CC_Draw_Shape(surface, scheme->Converter, unknown_beacon_shape_84e98c,
                  ((unknown_flags & 2) ? half : 0) + Frame % half, pixel, rect, 0x600, 0, 0, 0, 1000, 0, 0,
                  Point2D(0, 0));
    if (wcslen(unknown_text.chars) == 0) {
        return;
    }
    UnknownBeaconText text = unknown_text;
    if (unknown_flags & 2) {
        if (unknown_flag_a3dc89 && timeGetTime() % 500 < 250) {
            unsigned short *cursor = wcsrchr(text.chars, 0x5f);
            if (cursor && wcslen(cursor) == 1) {
                *cursor = 0x20;
            }
        }
    }
    if (!((unknown_flags & 2) && unknown_flag_a3dc89)) {
        unsigned short *cursor = wcsrchr(text.chars, 0x5f);
        if ((cursor && wcslen(cursor) == 1) || ((cursor = wcsrchr(text.chars, 0x20)) && wcslen(cursor) == 1)) {
            *cursor = 0;
        }
    }
    BitFontClass *font = BitFont;
    int width = 0;
    int height = 0;
    font->Get_Text_Area(text.chars, &width, &height, 200);
    Rect box(pixel.X - width / 2 - 4, pixel.Y + 32, width + 8, height + 8);
    RGBClass color = scheme->BaseColor.To_RGB();
    Rect fill = Intersect(box, rect, 0, 0);
    unsigned pixel_color = ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
                         | ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
                         | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
    surface->Fill_Rect(fill, 0);
    surface->Draw_Rect(fill, pixel_color);
    font->Set_Clipping(true);
    tagRECT clip;
    clip.left = rect.X;
    clip.top = rect.Y;
    clip.right = rect.X + rect.Width - 1;
    clip.bottom = rect.Y + rect.Height - 1;
    font->Set_Clip_Box(&clip);
    font->Set_Color((unsigned short)pixel_color);
    BitText->Print_Box(font, surface, text.chars, box.X + 4, box.Y + 4, 200, box.Height, 0, 0, 0);
}
