// void Voc_Static_Finish_At(CoordStruct const &coord, unsigned int flags)
// (0x007143B0): lets the static sounds at a coordinate that have any of the
// flags end (hypothesis).
#include "shared/voc_static.hpp"
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0
// @ref ?Audio_Event_Handle_Finish@@YIXPAUAudioEventHandle@@@Z=00405fe0

void __fastcall Voc_Static_Finish_At(CoordStruct const &coord, unsigned int flags)
{
    for (VocStaticSound *sound = (VocStaticSound *)Audio_List_First(&unknown_voc_static_list_ad07d0); sound != 0;
         sound = (VocStaticSound *)Audio_List_Next(sound)) {
        if ((sound->Flags & flags) && sound->Coord.X == coord.X && sound->Coord.Y == coord.Y && sound->Coord.Z == coord.Z) {
            Audio_Event_Handle_Finish(&sound->Handle);
        }
    }
}
