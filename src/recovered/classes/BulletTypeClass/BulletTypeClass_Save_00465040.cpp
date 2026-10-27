// HRESULT __stdcall BulletTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x00465040)
#include "shared/bullet_type.hpp"

HRESULT __stdcall BulletTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
