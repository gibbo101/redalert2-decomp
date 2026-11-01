// void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before) (0x005A02B0)
#include "shared/play_movie.hpp"

void __fastcall Play_Movie(char const *name, int theme, bool clrscrn_after, bool stretch, bool clrscrn_before)
{
    Play_Movie(name, theme, clrscrn_after, stretch, clrscrn_before, true);
}
