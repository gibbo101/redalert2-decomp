// TiberiumClass::Save (0x006E93B0)
#include "shared/tiberium.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall TiberiumClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = AbstractClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    Debris.Save(stream);
    return S_OK;
}
