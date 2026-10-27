// void ThemeClass::Save(IStream *stream) -- 0x006E8310 (name hypothesis)
// Purpose: writes the playing (+0x04) and suspended (+0x08) themes to a
// save stream, stopping after a failed write.
// Assumptions: layout as in ThemeClass::Suspend (0x006E8270); the result
// is not returned.
#include "shared/com_persist.hpp"

class ThemeClass {
public:
    void Save(IStream *stream);

    int Current;                    // +0x00
    int Playing;                    // +0x04
    int Suspended;                  // +0x08
};

void ThemeClass::Save(IStream *stream)
{
    if (SUCCEEDED(stream->Write(&Playing, sizeof(Playing), 0))) {
        stream->Write(&Suspended, sizeof(Suspended), 0);
    }
}
