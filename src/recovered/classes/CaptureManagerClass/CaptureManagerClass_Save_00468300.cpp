// ?Save@CaptureManagerClass@@UAGJPAUIStream@@H@Z (0x00468300)
// Only the AbstractClass part.
#include "shared/capture_manager.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall CaptureManagerClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
