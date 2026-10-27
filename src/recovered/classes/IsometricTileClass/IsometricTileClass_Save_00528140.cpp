// HRESULT __stdcall IsometricTileClass::Save(IStream *stream, BOOL clear_dirty) (0x00528140)
#include "shared/isometric_tile.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall IsometricTileClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
