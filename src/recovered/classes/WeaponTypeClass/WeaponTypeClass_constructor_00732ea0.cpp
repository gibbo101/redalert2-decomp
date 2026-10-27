// WeaponTypeClass::WeaponTypeClass(char const *ini_name) (0x00732EA0)
#include "shared/weapon_type.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_7WeaponTypeClass@@6BIPersistStream@@@=007af470
// @ref ??_7WeaponTypeClass@@6BIRTTITypeInfo@@@=007af444
// @ref ??_7WeaponTypeClass@@6BINoticeSink@@@=007af468
// @ref ??_7WeaponTypeClass@@6BINoticeSource@@@=007af460
// @ref ??_EWeaponTypeClass@@UAEPAXI@Z=00733ff0
// @ref ??_GWeaponTypeClass@@UAEPAXI@Z=00733ff0
// @ref ??0?$VectorClass@H@@QAE@ABV0@@Z=0046cfa0
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020
// @ref ??4?$VectorClass@H@@QAEAAV0@ABV0@@Z=0046db60
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ??_7?$TypeList@H@@6B@=0079d9f4
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$TypeList@H@@UAEPAXI@Z=0046cdd0
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
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
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ??0?$DynamicVectorClass@H@@QAE@IPBH@Z=0046d1f0
// @ref ??0?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE@IPBQAVAnimTypeClass@@@Z=0050b480
// @ref ??0RGBClass@@QAE@XZ=004a9af0
// @ref ??B?$FixedString@$0BJ@@@QBEPBDXZ=0050b0e0
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@ABVNoInitClass@@@Z=0050b100
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??0?$DynamicVectorClass@H@@QAE@ABVNoInitClass@@@Z=006df8a0
// @ref ?Add@?$DynamicVectorClass@H@@QAE_NABH@Z=0046d300
// @ref ?Add@?$DynamicVectorClass@PAVAnimTypeClass@@@@QAE_NABQAVAnimTypeClass@@@Z=0050b590
// @ref ??0?$TypeList@PAVAnimTypeClass@@@@QAE@ABV0@@Z=0050b7d0
// @ref ??_G?$DynamicVectorClass@PAVAnimTypeClass@@@@UAEPAXI@Z=0050b260
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_7?$DynamicVectorClass@PAVAnimTypeClass@@@@6B@=007a3b7c

WeaponTypeClass::WeaponTypeClass(char const *ini_name)
    : AbstractTypeClass(ini_name),
      unknown_98(0),
      Burst(1),
      Projectile(0),
      unknown_a4(0),
      unknown_a8(0),
      Warhead(0),
      unknown_b0(0),
      unknown_b4(0),
      unknown_b8(0),
      unknown_f4(0),
      unknown_f8(0),
      unknown_105(false),
      unknown_106(false),
      unknown_107(false),
      unknown_108(false),
      unknown_109(false),
      unknown_10a(false),
      unknown_10b(false),
      unknown_10c(false),
      unknown_10d(false),
      unknown_10e(false),
      unknown_10f(true),
      unknown_110(false),
      unknown_111(false),
      unknown_112(false),
      unknown_113(true),
      unknown_114(false),
      unknown_115(false),
      unknown_116(false),
      unknown_118(0),
      unknown_11c(false),
      unknown_11d(false),
      unknown_11e(false),
      unknown_11f(false),
      unknown_120(false),
      unknown_121(false),
      unknown_122(false),
      unknown_123(false),
      unknown_124(10),
      unknown_125(false),
      unknown_126(false),
      unknown_127(false),
      unknown_128(false),
      unknown_129(false),
      unknown_12a(false),
      unknown_12b(false),
      unknown_12c(0)
{
    AbstractClass::Create_ID();
    unknown_WeaponTypeClass_list_00839b90.Add(this);
}
