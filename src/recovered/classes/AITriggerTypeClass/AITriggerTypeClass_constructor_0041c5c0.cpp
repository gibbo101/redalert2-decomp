// ??0AITriggerTypeClass@@QAE@PBD@Z (0x0041C5C0)
// Defaults, listed in the AI trigger type list.
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_7AITriggerTypeClass@@6BINoticeSink@@@=0079b75c
// @ref ??_7AITriggerTypeClass@@6BINoticeSource@@@=0079b754
// @ref ??_7AITriggerTypeClass@@6BIPersistStream@@@=0079b780
// @ref ??_7AITriggerTypeClass@@6BIRTTITypeInfo@@@=0079b764
// @ref ??_EAITriggerTypeClass@@UAEPAXI@Z=0041e290
// @ref ??_GAITriggerTypeClass@@UAEPAXI@Z=0041e290
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@AITriggerTypeClass@@UBEXAAVWWCRCEngine@@@Z=0041c850
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?GetClassID@AITriggerTypeClass@@UAGJPAUGUID@@@Z=0041c770
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@AITriggerTypeClass@@UBEHXZ=0041e270
// @ref ?Load@AITriggerTypeClass@@UAGJPAUIStream@@@Z=0041c7b0
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Read_INI@AITriggerTypeClass@@UAE_NAAVCCINIClass@@@Z=0041d7e0
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@AITriggerTypeClass@@UAGJPAUIStream@@H@Z=0041c830
// @ref ?Size_Of@AITriggerTypeClass@@UBEHXZ=0041e280
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?Write_INI@AITriggerTypeClass@@UBE_NAAVCCINIClass@@@Z=0041dd60
// @ref ?AITriggerTypes@@3V?$DynamicVectorClass@PAVAITriggerTypeClass@@@@A=00a3d260
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
// @ref ?unknown_slot24@AbstractTypeClass@@UAEXH@Z=004109a0
#include "shared/ai_trigger_type.hpp"

AITriggerTypeClass::AITriggerTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    ConditionType(-1),
    unknown_9c(0),
    unknown_a0(0),
    unknown_a4(false),
    unknown_a8(-1),
    unknown_ac(0),
    unknown_b0(0),
    Weight(1.0),
    MinWeight(1.0),
    MaxWeight(1.0),
    unknown_d0(false),
    unknown_d1(false),
    unknown_d2(true),
    unknown_d3(true),
    unknown_d4(true),
    unknown_d8(0),
    unknown_dc(0),
    unknown_e0(0),
    unknown_104(0),
    unknown_108(0)
{
    memset(Comparator, 0, sizeof(Comparator));
    AITriggerTypes.Add(this);
}
