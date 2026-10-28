// HRESULT __stdcall TerrainTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x006E59C0)
#include "shared/terrain_type.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall TerrainTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
