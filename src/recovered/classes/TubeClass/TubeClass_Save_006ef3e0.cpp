// HRESULT __stdcall TubeClass::Save(IStream *stream, BOOL clear_dirty) (0x006EF3E0)
#include "shared/tube.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall TubeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
