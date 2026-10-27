// ??0CaptureManagerClass@@QAE@PAVAbstractClass@@@Z (0x00467DB0)
// Manager for owner; listed in the unit list.
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7CaptureManagerClass@@6BINoticeSink@@@=0079d794
// @ref ??_7CaptureManagerClass@@6BINoticeSource@@@=0079d78c
// @ref ??_7CaptureManagerClass@@6BIPersistStream@@@=0079d7b8
// @ref ??_7CaptureManagerClass@@6BIRTTITypeInfo@@@=0079d79c
// @ref ??_ECaptureManagerClass@@UAEPAXI@Z=00468380
// @ref ??_GCaptureManagerClass@@UAEPAXI@Z=00468380
// @ref ?AI@AbstractClass@@UAEXXZ=00410310
// @ref ?AddRef@AbstractClass@@UAGKXZ=004100a0
// @ref ?AddRef@AbstractClass@@W3AGKXZ=00410390
// @ref ?Center_Coord@AbstractClass@@UBE?AUCoordStruct@@XZ=00410260
// @ref ?Compute_CRC@CaptureManagerClass@@UBEXAAVWWCRCEngine@@@Z=00468220
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?Detach@AbstractClass@@UAEXPAV1@_N@Z=00410220
// @ref ?Fetch_ID@AbstractClass@@UAGJXZ=0040ffc0
// @ref ?GetClassID@CaptureManagerClass@@UAGJPAUGUID@@@Z=00468320
// @ref ?GetSizeMax@AbstractClass@@UAGJPATULARGE_INTEGER@@@Z=00410180
// @ref ?INoticeSink_Unknown@AbstractClass@@UAE_NHH@Z=00410320
// @ref ?INoticeSource_Unknown@AbstractClass@@UAGXXZ=00410330
// @ref ?Init@AbstractClass@@UAEXXZ=00410210
// @ref ?IsDirty@AbstractClass@@UAGJXZ=004101f0
// @ref ?Kind_Of@CaptureManagerClass@@UBEHXZ=00468370
// @ref ?Load@CaptureManagerClass@@UAGJPAUIStream@@@Z=00468280
// @ref ?Owner@AbstractClass@@UBEHXZ=00410230
// @ref ?Owning_House@AbstractClass@@UBEPAVHouseClass@@XZ=00410240
// @ref ?QueryInterface@AbstractClass@@UAGJABUGUID@@PAPAX@Z=00410000
// @ref ?QueryInterface@AbstractClass@@W3AGJABUGUID@@PAPAX@Z=00410380
// @ref ?Release@AbstractClass@@UAGKXZ=004100b0
// @ref ?Release@AbstractClass@@W3AGKXZ=004103a0
// @ref ?Save@CaptureManagerClass@@UAGJPAUIStream@@H@Z=00468300
// @ref ?Size_Of@CaptureManagerClass@@UBEHXZ=00468360
// @ref ?What_Am_I@AbstractClass@@UAGHXZ=0040ffb0
// @ref ?unknown_slot16@AbstractClass@@UBEHXZ=00410250
// @ref ?unknown_slot17@AbstractClass@@UBE_NXZ=004101e0
// @ref ?unknown_slot19@AbstractClass@@UBE?AUCoordStruct@@PAVTechnoClass@@@Z=00410290
// @ref ?unknown_slot20@AbstractClass@@UBE_NXZ=004102c0
// @ref ?unknown_slot21@AbstractClass@@UBE_NXZ=004102d0
// @ref ?unknown_slot22@AbstractClass@@UBE?AUCoordStruct@@XZ=004102e0
#include "shared/capture_manager.hpp"

CaptureManagerClass::CaptureManagerClass(AbstractClass *owner)
{
    unknown_24 = 0;
    unknown_28 = 0;
    Owner = owner;
    unknown_CaptureManagerClass_list_008505a0.Add(this);
}
