// void FootClass::unknown_slot260(AbstractClass *target, int arg2) (0x004C8030)
// Sets the navigation target (+0x494; hypothesis: Assign_Destination):
// with a target, the old waypoint marker (+0x25C) goes, a hover locomotor
// restarts its timer +0x530, and unless +0x598 asks to skip once the
// locomotor moves to the target's slot 19 coordinate; without one, the
// locomotor stops (except an aircraft attacking in mission 1). Then the
// movement timers +0x558 (rules +0x13D0) and +0x530 restart.
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref __com_issue_error@4=00795940
// @ref _unknown_uuid_IPersist_7cf208=007cf208
// @ref _CLSID_HoverLocomotionClass=007a1f80
// @ref ?Query@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454bf0
// @ref ?Release_Held@?$UnknownComPtr@UIPersist@@$1?unknown_uuid_IPersist_7cf208@@3UGUID@@B@@QAEXXZ=004a4d00
// @ref ?Frame@@3HA=00a40d2c

extern "C" GUID const CLSID_HoverLocomotionClass;   // 0x007A1F80

void FootClass::unknown_slot260(AbstractClass *target, int arg2)
{
    unknown_490 = 0;
    unknown_494 = target;
    if (target != 0) {
        if (unknown_25c[0] != 0) {
            unknown_25c[0]->unknown_slot60();
            unknown_25c[0] = 0;
        }
        UnknownComPtr<IPersist, &unknown_uuid_IPersist_7cf208> persist(Locomotor);
        GUID clsid;
        persist.Checked()->GetClassID(&clsid);
        if (memcmp(&clsid, &CLSID_HoverLocomotionClass, sizeof(GUID)) == 0 && unknown_530.Value() == 0) {
            unknown_530 = CDTimerClass<FrameTimerClass>(1);
        }
        if (unknown_598) {
            unknown_598 = false;
        } else {
            CoordStruct coord = unknown_494->unknown_slot19(this);
            Locomotor.Checked()->Move_To(coord);
        }
    } else if (Kind_Of() != 2 || (Mission != 1 && MissionQueue != 1) || unknown_228 == 0) {
        Locomotor.Checked()->Stop_Moving();
        unknown_494 = 0;
    }
    unknown_5a1 = false;
    unknown_558 = CDTimerClass<FrameTimerClass>(Rules->unknown_13d0);
    unknown_530 = CDTimerClass<FrameTimerClass>(0);
}
