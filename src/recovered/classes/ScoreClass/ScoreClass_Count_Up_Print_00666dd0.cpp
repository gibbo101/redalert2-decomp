// Rect ScoreClass::Count_Up_Print(Surface *surface, unsigned short const *format, int value, int max, int x, int y) (0x00666DD0)
// Prints min(value, max) with format so its baseline is at y and returns
// the printed area.
#include "shared/score.hpp"
#include "shared/string_table.hpp"

Rect ScoreClass::Count_Up_Print(Surface *surface, unsigned short const *format, int value, int max, int x, int y)
{
    unsigned short buffer[64];
    swprintf((wchar_t *)buffer, (wchar_t const *)format, value < max ? value : max);
    y -= Font->Height;
    Font->Print(surface, buffer, x, y, 2);
    return Rect(x, y, Font->String_Pixel_Width(buffer), Font->Height);
}
