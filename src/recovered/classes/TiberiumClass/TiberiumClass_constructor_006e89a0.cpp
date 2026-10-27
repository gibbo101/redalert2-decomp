// TiberiumClass::TiberiumClass(char const *ini_name) (0x006E89A0)
#include "shared/tiberium.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_ETiberiumClass@@UAEPAXI@Z=006ea9f0
// @ref ??_GTiberiumClass@@UAEPAXI@Z=006ea9f0
// @ref ??_7TiberiumClass@@6BIPersistStream@@@=007ad8b0
// @ref ??_7TiberiumClass@@6BIRTTITypeInfo@@@=007ad894
// @ref ??_7TiberiumClass@@6BINoticeSink@@@=007ad88c
// @ref ??_7TiberiumClass@@6BINoticeSource@@@=007ad884
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ??0?$VectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b860
// @ref ??4?$VectorClass@PAVAnimTypeClass@@@@QAEAAV0@ABV0@@Z=006534d0
// @ref ??8?$VectorClass@PAVAnimTypeClass@@@@UBE_NABV0@@Z=0050b300
// @ref ??_7?$TypeList@PAVAnimTypeClass@@@@6B@=007a3b3c
// @ref ??_7?$VectorClass@PAVAnimTypeClass@@@@6B@=007a3b5c
// @ref ??_E?$TypeList@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b200
// @ref ??_E?$VectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b2b0
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
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

TiberiumClass::TiberiumClass(char const *ini_name)
    : AbstractTypeClass(ini_name),
      ArrayIndex(-1),
      unknown_9c(0),
      unknown_a0(0.1),
      unknown_a8(0),
      unknown_b0(0.1),
      Value(0),
      unknown_bc(0),
      unknown_c0(0),
      Image(0),
      unknown_e4(0),
      NumFrames(0),
      NumImages(0),
      unknown_f0(0),
      unknown_f4(0),
      unknown_f8(0),
      unknown_fc(0),
      unknown_10c(0),
      unknown_110(0),
      unknown_114(0),
      unknown_118(0)
{
    ArrayIndex = unknown_TiberiumClass_list_00ac0b30.Count();
    unknown_TiberiumClass_list_00ac0b30.Add(this);
    unknown_c4.Clear();
    unknown_objects_ac0cb0.Add(this);
}
