// HRESULT __stdcall BuildingLightClass::Load(IStream *stream) (0x004340E0)
// Restores the light in place and swizzles its owner and followed object.
#include "shared/building_light.hpp"
// @ref ?Load@ObjectClass@@UAGJPAUIStream@@@Z=005d4760
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
// @ref ??_7BuildingLightClass@@6BIPersistStream@@@=0079c7e0
// @ref ??_7BuildingLightClass@@6BIRTTITypeInfo@@@=0079c7c4
// @ref ??_7BuildingLightClass@@6BINoticeSink@@@=0079c7bc
// @ref ??_7BuildingLightClass@@6BINoticeSource@@@=0079c7b4
// @ref ??_EBuildingLightClass@@UAEPAXI@Z=00434850
// @ref ??_GBuildingLightClass@@UAEPAXI@Z=00434850
// @ref ?AI@BuildingLightClass@@UAEXXZ=00433970
// @ref ?unknown_slot52@BuildingLightClass@@UAE_NXZ=004347c0
// @ref ?unknown_slot53@BuildingLightClass@@UAE_NHH@Z=004347e0
// @ref ?unknown_slot67@BuildingLightClass@@UAEXHH@Z=00433380

HRESULT __stdcall BuildingLightClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) BuildingLightClass(NoInitClass());
        SwizzleManager.Swizzle((void **)&Owner);
        SwizzleManager.Swizzle((void **)&Following);
    }
    return result;
}
