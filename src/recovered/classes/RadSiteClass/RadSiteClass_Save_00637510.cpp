// ?Save@RadSiteClass@@UAGJPAUIStream@@H@Z (0x00637510)
// Only the AbstractClass part.
#include "shared/radsite.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall RadSiteClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
