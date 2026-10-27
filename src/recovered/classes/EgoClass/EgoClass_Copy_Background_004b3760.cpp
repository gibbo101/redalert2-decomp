#include "shared/ego.hpp"
#include "shared/text_print.hpp"
extern int unknown_8523e0;
// @ref ?unknown_8523e0@@3HA=008523e0
void EgoClass::Copy_Background(Surface *source)
{
    BitFontClass *font = Font_For_Style(TextFlags);
    font->String_Pixel_Width(Text, 0);
    Rect area(0, Y, unknown_8523e0, 18);
    unknown_surface_83995c->Copy_From(area, *source, area, false, true);
}
