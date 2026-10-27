// MSSfxEntry *MapSelect::Find_Sound(Wstring const &name) const (0x005B0980)
// Sound entry of that name, ignoring case; null without sound.
#include "shared/ms_choice.hpp"
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?To_Lower@Wstring@@QAEXXZ=0076ee20

MSSfxEntry *MapSelect::Find_Sound(Wstring const &name) const
{
    if (unknown_check_406f30()) {
        for (int index = 0; index < Sounds.Count(); index++) {
            MSSfxEntry *sound = Sounds[index];
            Wstring entry(sound->Name);
            entry.To_Lower();
            Wstring wanted(name);
            wanted.To_Lower();
            if (entry == wanted) {
                return sound;
            }
        }
    }
    return 0;
}
