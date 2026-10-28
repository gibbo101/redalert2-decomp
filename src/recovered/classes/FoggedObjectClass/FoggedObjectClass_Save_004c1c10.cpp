// HRESULT __stdcall FoggedObjectClass::Save(IStream *stream, BOOL clear_dirty) (0x004C1C10)
// Saves the base object, then the draw record count and each 16-byte draw record.
#include "shared/fogged_object.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall FoggedObjectClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        int count = DrawRecords.Count();
        result = stream->Write(&count, sizeof(count), 0);
        if (SUCCEEDED(result)) {
            for (int index = 0; index < count; index++) {
                result = stream->Write(&DrawRecords[index], sizeof(DrawRecord), 0);
                if (FAILED(result)) {
                    return S_OK;
                }
            }
            return S_OK;
        }
    }
    return result;
}
