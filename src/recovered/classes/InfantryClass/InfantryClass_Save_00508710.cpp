// HRESULT __stdcall InfantryClass::Save(IStream *stream, BOOL clear_dirty) (0x00508710, slot 6)
#include "shared/infantry.hpp"
// @ref ?Save@FootClass@@UAGJPAUIStream@@H@Z=004c9fe0

HRESULT __stdcall InfantryClass::Save(IStream *stream, BOOL clear_dirty)
{
    return FootClass::Save(stream, clear_dirty);
}
