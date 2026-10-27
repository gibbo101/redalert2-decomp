// void __fastcall Audio_Source_Reset(AudioSource *source) -- 0x00408400
// Purpose: empties the source (no data, size, format or pieces).
#include "shared/audio.hpp"

void __fastcall Audio_Source_Reset(AudioSource *source)
{
    source->unknown_00 = 0;
    source->unknown_04 = 0;
    source->Format = 0;
    source->unknown_18 = 0;
    Audio_List_Init(&source->Pieces);
}
