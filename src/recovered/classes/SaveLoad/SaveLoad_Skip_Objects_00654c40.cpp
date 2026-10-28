// HRESULT __fastcall Skip_Objects(IStream *stream) (0x00654C40; name hypothesis)
// Reads a count, then loads that many OLE objects and drops them (each one
// leaks: the original never releases them).
// SaveLoad.cpp expands the smart pointers' Release_Held inline (shared/com_ptr.hpp).
#define COM_PTR_IMPLEMENT_RELEASE
#include "shared/com_persist.hpp"
// @ref ?unknown_savegame_streams_7f1c10@@3QBUSavegameStreamName@@B=007f1c10
// @ref _unknown_fmtid_7afd60=007afd60


HRESULT __fastcall Skip_Objects(IStream *stream)
{
    int count;
    IUnknown *object;
    HRESULT result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = OleLoadFromStream(stream, IID_IUnknown_7afce0, (void **)&object);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}
