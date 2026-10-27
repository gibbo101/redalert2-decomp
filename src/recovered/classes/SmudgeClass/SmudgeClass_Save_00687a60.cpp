// HRESULT __stdcall SmudgeClass::Save(IStream *stream, BOOL clear_dirty) (0x00687A60)
#include "shared/smudge.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall SmudgeClass::Save(IStream *stream, BOOL clear_dirty)
{
    return ObjectClass::Save(stream, clear_dirty);
}
