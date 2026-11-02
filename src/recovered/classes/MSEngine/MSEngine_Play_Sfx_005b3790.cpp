// void MSEngine::Play_Sfx(char const *name, int volume) (0x005B3790)
// Plays the named sound effect (case-insensitive match) at volume scaled by the sound effect volume; nothing
// when name is null or sound is unavailable. No direct callers (the inventory has no row; the bound is a linear
// sweep). The name read through a local gives the original's registers (this in ebx, the entry in edi).
#include "shared/ms_engine.hpp"
// @ref ?Play@MSSfx@@QAEXH@Z=005b69f0
// @ref ?unknown_volume_a40b44@@3MA=00a40b44

void MSEngine::Play_Sfx(char const *name, int volume)
{
    if (name != 0 && unknown_check_406f30()) {
        for (int i = 0; i < Sfx.Count(); i++) {
            MSSfx *sfx = Sfx[i];
            char const *sfx_name = sfx->Name;
            if (_stricmp(name, sfx_name) == 0) {
                sfx->Play(volume * unknown_volume_a40b44);
                return;
            }
        }
    }
}
