// HRESULT __stdcall RadioClass::Save(IStream *stream, BOOL clear_dirty) (0x00636D20, slot 6)
// MissionClass's part, then the contact vector's size and its pointers.
#include "shared/radio.hpp"
#include "shared/techno.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall RadioClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = MissionClass::Save(stream, clear_dirty);
    if (FAILED(result)) {
        return result;
    }
    int count = RadioLinks.Length();
    result = stream->Write(&count, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    for (int index = 0; index < count; index++) {
        result = stream->Write(&RadioLinks[index], 4, 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return S_OK;
}
