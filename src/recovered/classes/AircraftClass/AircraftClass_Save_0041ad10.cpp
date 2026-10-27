// HRESULT __stdcall AircraftClass::Save(IStream *stream, BOOL clear_dirty) (0x0041AD10, slot 6)
#include "shared/aircraft.hpp"
// @ref ?Save@FootClass@@UAGJPAUIStream@@H@Z=004c9fe0

HRESULT __stdcall AircraftClass::Save(IStream *stream, BOOL clear_dirty)
{
    return FootClass::Save(stream, clear_dirty);
}
