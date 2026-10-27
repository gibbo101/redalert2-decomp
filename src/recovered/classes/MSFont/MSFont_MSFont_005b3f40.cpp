// MSFont::MSFont(bool sidebar) (0x005B3F40)
// Clears the colour (RGBClass's default constructor), loads the shared font
// data and counts the instance.
#include "shared/msfont.hpp"
// @ref ??_7MSFont@@6B@=007a70b8
// @ref ?Load@MSFont@@QAE_N_N@Z=005b3fd0
// @ref ?unknown_font_count_a71858@@3HA=00a71858

MSFont::MSFont(bool sidebar)
{
    Load(sidebar);
    unknown_font_count_a71858++;
}
