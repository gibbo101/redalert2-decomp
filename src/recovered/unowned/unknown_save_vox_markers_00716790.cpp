// void __fastcall unknown_save_vox_markers(IStream *stream) -- 0x00716790
// Purpose: writes the two four-character markers 'SxoV' and 'ExoV'
// (0x566F7853, 0x566F7845) to a save stream, stopping after a failed
// write.
// Assumptions: what the markers bracket (EVA voice data?) is a guess.
#include "shared/com_persist.hpp"

void __fastcall unknown_save_vox_markers(IStream *stream)
{
    int marker = 0x566F7853;
    if (SUCCEEDED(stream->Write(&marker, sizeof(marker), 0))) {
        marker = 0x566F7845;
        stream->Write(&marker, sizeof(marker), 0);
    }
}
