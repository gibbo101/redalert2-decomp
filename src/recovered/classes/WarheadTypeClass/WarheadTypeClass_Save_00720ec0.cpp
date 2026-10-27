// HRESULT __stdcall WarheadTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00720EC0)
// The base object, then the animation list as a count and pointers.
#include "shared/warhead_type.hpp"

HRESULT __stdcall WarheadTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractTypeClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = AnimList.Count();
    stream->Write(&count, sizeof(count), 0);
    for (int i = 0; i < count; i++) {
        stream->Write(&AnimList[i], sizeof(AnimTypeClass *), 0);
    }
    return S_OK;
}
