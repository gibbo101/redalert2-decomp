// HRESULT __stdcall TerrainClass::Save(IStream *stream, BOOL clear_dirty) (0x006E4700)
#include "shared/terrain.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall TerrainClass::Save(IStream *stream, BOOL clear_dirty)
{
    return ObjectClass::Save(stream, clear_dirty);
}
