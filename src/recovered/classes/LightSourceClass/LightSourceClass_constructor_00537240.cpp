// LightSourceClass::LightSourceClass (0x00537240): create and register an
// initially inactive light with the supplied position, radius and tint.
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

LightSourceClass::LightSourceClass(CoordStruct coord, int visibility, int intensity, int red, int green, int blue) :
    Intensity(intensity), RedTint(red), GreenTint(green), BlueTint(blue), DetailLevel(2), Location(coord), Visibility(visibility), Activated(false)
{
    unknown_LightSourceClass_list_00a6e818.Add(this);
}
