#include "shared/map_select.hpp"
// @ref ??9Wstring@@QBE_NPBD@Z=0076dae0
// @ref ?Find_Sound@MapSelectData@@=005b0980
// @ref ?Play@MSSfxEntry@@=005b16d0
void MapSelect::Play_Sound_0058fd00(Wstring const &name)
{
    if(name!=0) {
        MSSfxEntry *sound=Choices.Find_Sound(name);
        if(sound) sound->Play();
    }
}
