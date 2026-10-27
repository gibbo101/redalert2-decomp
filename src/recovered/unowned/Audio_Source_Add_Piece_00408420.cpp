// void __fastcall Audio_Source_Add_Piece(AudioSource *source, AudioSourceInfo *piece) -- 0x00408420
// Purpose: appends a piece to the source, adding its size to the total.
#include "shared/audio.hpp"

void __fastcall Audio_Source_Add_Piece(AudioSource *source, AudioSourceInfo *piece)
{
    Audio_List_Add_Tail(&source->Pieces, piece);
    source->unknown_04 += piece->unknown_10;
    piece->Source = source;
}
