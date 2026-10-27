// void GraphicMenuItem::Play_Sound(int) -- 0x004E01E0
// Plays the item's sound entry, if any (MSSfxEntry::Play 0x005B16D0).
#include "shared/graphic_menu.hpp"
// @ref ?Play@MSSfxEntry@@QAEXXZ=005b16d0

void GraphicMenuItem::Play_Sound(int unknown)
{
    if (Sound != 0) {
        Sound->Play();
    }
}
