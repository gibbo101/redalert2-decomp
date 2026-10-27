// HRESULT __stdcall AircraftTypeClass::Save(IStream *stream, BOOL clear_dirty) (0x0041C1F0)
#include "shared/aircraft_type.hpp"
// @ref ?Save@TechnoTypeClass@@UAGJPAUIStream@@H@Z=006dec10

HRESULT __stdcall AircraftTypeClass::Save(IStream *stream, BOOL clear_dirty)
{
    HRESULT result = TechnoTypeClass::Save(stream, clear_dirty);
    if (SUCCEEDED(result)) {
        result = S_OK;
    }
    return result;
}
