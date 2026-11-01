// void unknown_clear_font_cache_735d90() (0x00735D90)
// @ref ?unknown_font_cache_b25dc8@@3UUnknownFontCache@@A=00b25dc8
#include "shared/win_util.hpp"

void unknown_clear_font_cache_735d90()
{
    unknown_font_cache_b25dc8.Count = 0;
    operator delete(unknown_font_cache_b25dc8.Vector);
}
