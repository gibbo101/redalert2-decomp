#include "shared/player_profile.hpp"
unsigned int PlayerProfile::Set_Color_007399d0(unsigned int color)
{
    if (color != (unsigned int)Color) {
        Color = color;
        unknown_08 = true;
    }
    return color;
}
