// AudioEvent *Voc_Static_Add(int voc, CoordStruct const &coord, unsigned int flags)
// (0x00714290): a static sound: a node from the pool with a fresh handle, the
// coordinate and flags, the sound played there and the node listed; counts the
// static sounds and their maximum (name hypothesis).
#include "shared/voc_static.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0
// @ref ?unknown_voc_static_pool_ad0844@@3PAUAudioPool@@A=00ad0844
// @ref ?Init@UnknownAudioController@@QAEXXZ=00405bf0
// @ref ?Audio_Static_Sound_Count@@3HA=00ad0848
// @ref ?Audio_Static_Sound_Maximum@@3HA=00ad084c
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

AudioEvent *__fastcall Voc_Static_Add(int voc, CoordStruct const &coord, unsigned int flags)
{
    if (voc < 0) {
        return 0;
    }
    VocStaticSound *sound = (VocStaticSound *)Audio_Pool_Alloc(unknown_voc_static_pool_ad0844);
    if (sound == 0) {
        return 0;
    }
    sound->Handle.Init();
    Audio_List_Init_Node(sound);
    sound->PauseCount = 0;
    sound->Coord = coord;
    sound->Flags = flags;
    AudioEvent *event = Voc_Play_At(voc, sound->Coord, &sound->Handle);
    Audio_List_Add_Tail(&unknown_voc_static_list_ad07d0, sound);
    Audio_Static_Sound_Count++;
    if (Audio_Static_Sound_Count > Audio_Static_Sound_Maximum) {
        Audio_Static_Sound_Maximum = Audio_Static_Sound_Count;
    }
    return event;
}
