// ??0CampaignClass@@QAE@PBD@Z (0x00465450)
// A campaign named ini_name, listed in the campaign list, with an empty description.
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_7CampaignClass@@6BINoticeSink@@@=0079d67c
// @ref ??_7CampaignClass@@6BINoticeSource@@@=0079d674
// @ref ??_7CampaignClass@@6BIPersistStream@@@=0079d6a0
// @ref ??_7CampaignClass@@6BIRTTITypeInfo@@@=0079d684
// @ref ??_ECampaignClass@@UAEPAXI@Z=00465970
// @ref ??_GCampaignClass@@UAEPAXI@Z=00465970
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@CampaignClass@@UBEXAAVWWCRCEngine@@@Z=004658a0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?GetClassID@CampaignClass@@UAGJPAUGUID@@@Z=00465860
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@CampaignClass@@UBEHXZ=00465960
// @ref ?Load@CampaignClass@@UAGJPAUIStream@@@Z=004658e0
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Read_INI@CampaignClass@@UAE_NAAVCCINIClass@@@Z=004655c0
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@CampaignClass@@UAGJPAUIStream@@H@Z=00465930
// @ref ?Size_Of@CampaignClass@@UBEHXZ=00465950
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?Write_INI@AbstractTypeClass@@UBE_NAAVCCINIClass@@@Z=00410910
// @ref ?Campaigns@@3V?$DynamicVectorClass@PAVCampaignClass@@@@A=00a35d60
// @ref ?unknown_empty_wide_839d4c@@3QB_WB=00839d4c
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
// @ref ?unknown_slot24@AbstractTypeClass@@UAEXH@Z=004109a0
// @ref _wcscpy=00783689
#include "shared/campaign.hpp"

CampaignClass::CampaignClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    unknown_98(-1),
    unknown_29c(-1)
{
    Campaigns.Add(this);
    Scenario[0] = '\0';
    wcscpy(Description, unknown_empty_wide_839d4c);
}
