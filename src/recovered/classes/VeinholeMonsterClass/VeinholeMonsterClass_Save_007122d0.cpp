// HRESULT __stdcall VeinholeMonsterClass::Save(IStream *stream, BOOL clear_dirty) (0x007122D0)
#include "shared/veinhole.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall VeinholeMonsterClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
