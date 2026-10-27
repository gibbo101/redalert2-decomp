// HRESULT __stdcall IsometricTileTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0052E2B0, slot 6)
// The object type's save; S_OK when it succeeded.
// Only the list accessors expand here: the colour table constructor stays a call.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/isometric_tile_type.hpp"
// @ref ?Save@ObjectTypeClass@@UAGJPAUIStream@@H@Z=005d7e60

HRESULT __stdcall IsometricTileTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = ObjectTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
