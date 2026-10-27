// bool UnknownBlock_a3d2b0::Save(IStream *stream) -- 0x00672830
// Purpose: writes the 0xEC-byte block (a 4-byte length, then the block
// itself) to the stream; false when there is no stream or a write fails.
// Called for the global block at 0x00A3D2B0 by the save-game writer
// (0x00656825).
// Assumptions: the block is a plain 0xEC-byte structure saved by raw copy;
// its owner and contents are not identified.
#include "shared/com_persist.hpp"

struct UnknownBlock_a3d2b0 {
    bool Save(IStream *stream);

    char unknown_00[0xEC];
};

bool UnknownBlock_a3d2b0::Save(IStream *stream)
{
    if (stream) {
        int size = sizeof(*this);
        if (SUCCEEDED(stream->Write(&size, sizeof(size), 0))) {
            if (SUCCEEDED(stream->Write(this, size, 0))) {
                return true;
            }
        }
    }
    return false;
}
