// bool MSEngine::Add_Sfx(char const *name, int unknown2) (0x005B3710)
// Adds a named sound effect (no direct callers).
#include "shared/ms_engine.hpp"
// @ref ??0MSSfx@@QAE@PBDH@Z=005b69b0

bool MSEngine::Add_Sfx(char const *name, int unknown2)
{
    if (name != 0 && unknown2 != 0) {
        MSSfx *sfx = new MSSfx(name, unknown2);
        return Sfx.Add(sfx);
    }
    return false;
}
