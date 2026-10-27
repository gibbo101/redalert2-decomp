// HRESULT __stdcall BuildingLightClass::Save(IStream *stream, BOOL clear_dirty) (0x00434150)
#include "shared/building_light.hpp"
// @ref ?Save@AbstractClass@@UAGJPAUIStream@@H@Z=004100c0

HRESULT __stdcall BuildingLightClass::Save(IStream *stream, BOOL clear_dirty)
{
    return AbstractClass::Save(stream, clear_dirty);
}
