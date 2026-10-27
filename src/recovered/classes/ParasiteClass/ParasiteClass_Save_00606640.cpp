// ?Save@ParasiteClass@@UAGJPAUIStream@@H@Z (0x00606640)
// Only the AbstractClass part.
#include "shared/parasite.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall ParasiteClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
