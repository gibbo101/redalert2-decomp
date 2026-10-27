// HRESULT __stdcall TechnoClass::Save(IStream *stream, BOOL clear_dirty) (0x006D6A80, slot 6)
// RadioClass::Save; always S_OK.
#include "shared/techno.hpp"
// @ref ?Save@RadioClass@@UAGJPAUIStream@@H@Z=00636d20

HRESULT __stdcall TechnoClass::Save(IStream *stream, BOOL clear_dirty)
{
    RadioClass::Save(stream, clear_dirty);
    return S_OK;
}
