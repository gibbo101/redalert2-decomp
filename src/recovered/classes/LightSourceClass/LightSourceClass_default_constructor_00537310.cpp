// LightSourceClass::LightSourceClass() (0x00537310): an unlit light at the
// zero coordinate; added to the light list.
#include "shared/light_source.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7LightSourceClass@@6BIPersistStream@@@=007a5560
// @ref ??_7LightSourceClass@@6BIRTTITypeInfo@@@=007a5544
// @ref ??_7LightSourceClass@@6BINoticeSink@@@=007a553c
// @ref ??_7LightSourceClass@@6BINoticeSource@@@=007a5534
// @ref ?Kind_Of@LightSourceClass@@UBEHXZ=00537c20
// @ref ?Size_Of@LightSourceClass@@UBEHXZ=00537c10
// @ref ?GetClassID@LightSourceClass@@UAGJPAUGUID@@@Z=00537b60
// @ref ?Save@LightSourceClass@@UAGJPAUIStream@@H@Z=00537bf0
// @ref ?Compute_CRC@LightSourceClass@@UBEXAAVWWCRCEngine@@@Z=00537b50
// @ref _unknown_geometry_l=00a6e808

LightSourceClass::LightSourceClass() :
    Intensity(0),
    Tint(0, 0, 0),
    Location(unknown_geometry_l),
    Visibility(0),
    Activated(false)
{
    unknown_LightSourceClass_list_00a6e818.Add(this);
}
