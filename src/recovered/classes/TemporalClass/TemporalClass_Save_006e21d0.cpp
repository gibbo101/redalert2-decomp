// ?Save@TemporalClass@@UAGJPAUIStream@@H@Z (0x006E21D0)
// Only the AbstractClass part.
#include "shared/temporal.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall TemporalClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
