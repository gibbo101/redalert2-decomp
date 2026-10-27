// bool UnknownBlock_a3d2b0::Load(IStream *stream) -- 0x00672880
// Purpose: reads back the block written by Save (0x00672830): a 4-byte
// length that must be 0xEC, then the block itself; resets +0x04 to -1 after
// the read. False when there is no stream, a read fails or the length
// differs.
// Assumptions: as for Save; +0x04 is an index cleared on load.
#include "shared/com_persist.hpp"

struct UnknownBlock_a3d2b0 {
    bool Load(IStream *stream);

    int unknown_00;
    int unknown_04;
    char unknown_08[0xEC - 0x08];
};

bool UnknownBlock_a3d2b0::Load(IStream *stream)
{
    if (stream) {
        int size;
        if (SUCCEEDED(stream->Read(&size, sizeof(size), 0)) && size == sizeof(*this)) {
            HRESULT result = stream->Read(this, sizeof(*this), 0);
            unknown_04 = -1;
            if (SUCCEEDED(result)) {
                return true;
            }
        }
    }
    return false;
}
