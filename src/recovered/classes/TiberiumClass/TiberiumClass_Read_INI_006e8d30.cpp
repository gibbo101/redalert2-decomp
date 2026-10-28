// bool TiberiumClass::Read_INI(CCINIClass &ini) (0x006E8D30, slot 25)
// @ref $L12272=006e8fd0
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_05EFBF@Power?$AA@=007cfd44
// @ref ??_C@_05HIMK@Color?$AA@=007d13d8
// @ref ??_C@_05KBGO@Value?$AA@=007f84bc
// @ref ??_C@_05LADG@Image?$AA@=007cfddc
// @ref ??_C@_06FFHJ@Growth?$AA@=007f84d8
// @ref ??_C@_06ILBA@Spread?$AA@=007f84f4
// @ref ??_C@_06JIHM@Debris?$AA@=007f84b4
// @ref ??_C@_0BB@IGPH@SpreadPercentage?$AA@=007f84e0
// @ref ??_C@_0BB@PALC@GrowthPercentage?$AA@=007f84c4
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// Spread and growth rates, value, power, colour and debris animations, then
// the overlay image set chosen by "Image=" (-1 keeps the current one).
// Assumptions: overlay indices 27/127/147/102 are the first images of the
// four ore/gem/vein families; field names stay hypotheses.
// @ref ??8?$VectorClass@PAVAnimTypeClass@@@@UBE_NABV0@@Z=0050b300
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c
// @ref ??_7?$TypeList@PAVAnimTypeClass@@@@6B@=007a3b3c
// @ref ??_7?$VectorClass@PAVAnimTypeClass@@@@6B@=007a3b5c
// @ref ??_E?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_E?$TypeList@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b200
// @ref ??_E?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b2b0
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ??_G?$TypeList@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b200
// @ref ??_G?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b2b0
// @ref ?Clear@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b110
// @ref ?Clear@?$VectorClass@PAVAnimTypeClass@@@@UAEXXZ=0050b3f0
// @ref ?Fetch@?$VectorClass@PAVAnimTypeClass@@@@UBEPAVAnimTypeClass@@H@Z=0050b1f0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=0050b5e0
// @ref ?ID@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=0050b140
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHABQAVAnimTypeClass@@@Z=0050b420
// @ref ?ID@?$VectorClass@PAVAnimTypeClass@@@@UAEHPBQAVAnimTypeClass@@@Z=0050b460
// @ref ?Resize@?$DynamicVectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=0050b4e0
// @ref ?Resize@?$VectorClass@PAVAnimTypeClass@@@@UAE_NHPBQAVAnimTypeClass@@@Z=0050b340
#include "shared/tiberium.hpp"
#include "shared/ccini_class.hpp"
#include "shared/anim_type.hpp"
#include "shared/overlay_type.hpp"

bool TiberiumClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
        Spread = ini.Get_Int(ID, "Spread", Spread);
        unknown_a0 = ini.Get_Double(ID, "SpreadPercentage", unknown_a0);
        Growth = ini.Get_Int(ID, "Growth", Growth);
        unknown_b0 = ini.Get_Double(ID, "GrowthPercentage", unknown_b0);
        Value = ini.Get_Int(ID, "Value", Value);
        Power = ini.Get_Int(ID, "Power", Power);
        unknown_c0 = ini.Get_ColorScheme(ID, "Color", unknown_c0);
        Debris = TypeListReader<AnimTypeClass>::Get(ini, ID, "Debris", Debris);
        switch (ini.Get_Int(ID, "Image", -1)) {
            case -1:
                break;

            case 2:
                Image = OverlayTypes[27];
                unknown_e4 = 12;
                NumFrames = 12;
                break;

            case 3:
                Image = OverlayTypes[127];
                unknown_e4 = 12;
                NumFrames = 12;
                NumImages = 8;
                break;

            case 4:
                Image = OverlayTypes[147];
                unknown_e4 = 12;
                NumFrames = 12;
                NumImages = 8;
                break;

            default:
                Image = OverlayTypes[102];
                unknown_e4 = 12;
                NumFrames = 12;
                NumImages = 8;
                break;
        }
        return true;
    }
    return false;
}
