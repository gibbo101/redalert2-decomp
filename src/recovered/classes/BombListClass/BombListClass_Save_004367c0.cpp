// HRESULT BombListClass::Save(IStream *stream) (0x004367C0): both lists as
// a count and their pointers.
#include "shared/object.hpp"

HRESULT BombListClass::Save(IStream *stream)
{
    int count = Bombs.Count();
    HRESULT result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&Bombs[index], sizeof(BombClass *), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    count = unknown_18.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (index = 0; index < count; index++) {
        result = stream->Write(&unknown_18[index], sizeof(TechnoClass *), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return result;
}
