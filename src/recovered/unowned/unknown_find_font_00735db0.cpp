// HFONT __fastcall unknown_find_font_735db0(HDC dc, char const *face, int width, int height, unsigned attributes) (0x00735DB0)
// @ref ?unknown_font_cache_b25dc8@@3UUnknownFontCache@@A=00b25dc8
// @ref ?unknown_create_font_7360b0@@YIPAUHFONT__@@PAUHDC__@@PBDHHI@Z=007360b0
#include "shared/win_util.hpp"

HFONT __fastcall unknown_find_font_735db0(HDC dc, char const *face, int width, int height, unsigned attributes)
{
    for (int index = 0; index < unknown_font_cache_b25dc8.Count; index++) {
        UnknownFontEntry entry;
        unknown_font_cache_b25dc8.Get(index, entry);
        if (strcmp(entry.Face, face) == 0 && entry.Width == width && entry.Height == height
            && entry.Attributes == attributes) {
            return entry.Font;
        }
    }
    if (dc == 0) {
        return 0;
    }
    HFONT font = unknown_create_font_7360b0(dc, face, width, height, attributes);
    if (font == 0) {
        return font;
    }
    UnknownFontEntry entry;
    strcpy(entry.Face, face);
    entry.Width = width;
    entry.Height = height;
    entry.Attributes = attributes;
    entry.Font = font;
    unknown_font_cache_b25dc8.Add(entry);
    return font;
}
