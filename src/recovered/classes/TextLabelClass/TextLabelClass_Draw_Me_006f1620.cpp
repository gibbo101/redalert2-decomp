// int TextLabelClass::Draw_Me(int forced) (0x006F1620, slot 27)
// Prints the label (Tiberian Sun txtlabel.cpp's Draw_Me with RA2's edit text printer): nothing while
// hidden; clipped to the drawing surface's right edge; with IsRevealed one more character every
// 16 ms, with the message typing sound while characters remain. The caret shows while focused.
#include "shared/text_label.hpp"
#include "shared/color_scheme.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"
#include "shared/win32_api.hpp"
// @ref ?Draw_Me@GadgetClass@@UAEHH@Z=004cf240
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref _wcslen=00783605
// @ref ?unknown_draw_edit_text_600830@OwnerDraw@@YIXPAVSurface@@AAVRect@@PBGHPAVBitFontClass@@IPAHHHHH@Z=00600830

int TextLabelClass::Draw_Me(int forced)
{
    if (!IsHidden && GadgetClass::Draw_Me(forced)) {
        int index = Color;
        if (ColorSchemes.Count() != 0) {
            if (index <= 0 || index >= ColorSchemes.Count()) {
                index = 0;
            }
            ColorScheme *scheme = ColorSchemes[index];
            if (scheme != 0) {
                BitFontClass *font = Font_For_Style(Style);
                Rect rect;
                rect.X = X;
                rect.Y = Y;
                rect.Width = PixWidth < 0 ? unknown_surface_83995c->Get_Width() : PixWidth;
                rect.Height = font->Height;
                int over = rect.X + rect.Width - unknown_surface_83995c->Get_Width();
                if (over > 0) {
                    rect.Width -= over;
                    if (!rect.Is_Valid()) {
                        return false;
                    }
                }
                RGBClass rgb = scheme->BaseColor.To_RGB();
                unsigned color = rgb.Red | (rgb.Green << 8) | (rgb.Blue << 16);
                int length = wcslen(Text);
                if (IsRevealed) {
                    DWORD now = timeGetTime();
                    int count = RevealCount;
                    if (RevealCount == 0) {
                        RevealCount = 1;
                    } else {
                        RevealCount += (now - RevealTime) >> 4;
                    }
                    if (count != RevealCount) {
                        RevealTime = now;
                    }
                    if (RevealCount <= length) {
                        Voc_Play(Rules->MessageCharTyped, 1.0f, 0x2000, 0);
                    }
                }
                OwnerDraw::unknown_draw_edit_text_600830(unknown_surface_83995c, rect, Text, length, font, color,
                                                        &Scroll, Has_Focus(), 0, 1, RevealCount);
                return true;
            }
        }
    }
    return false;
}
