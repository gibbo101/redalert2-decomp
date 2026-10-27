// int FootClass::unknown_slot176() (0x004C9930)
// TechnoClass's slot 176 plus the largest of the type's Z fudges that
// apply (column, tunnel, cliff, bridge) plus the locomotor's Z adjustment.
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_slot176@TechnoClass@@UAEHXZ=006cfea0
// @ref ?unknown_6cf9d0@TechnoClass@@QAEHXZ=006cf9d0
// @ref ?unknown_6cfb60@TechnoClass@@QAEHXZ=006cfb60
// @ref ?unknown_6cfda0@TechnoClass@@QAEHXZ=006cfda0
// @ref ?unknown_6cf670@TechnoClass@@QAE_NXZ=006cf670

int FootClass::unknown_slot176()
{
    int adjust = 0;
    if (Locomotor) {
        adjust = Locomotor.Checked()->Z_Adjust();
    }
    int fudge = unknown_slot32()->ZFudgeColumn * unknown_6cf9d0();
    int tunnel = unknown_slot32()->ZFudgeTunnel * unknown_6cfb60();
    int cliff = unknown_slot32()->ZFudgeCliff * unknown_6cfda0();
    int bridge = 0;
    if (unknown_6cf670()) {
        bridge = unknown_slot32()->ZFudgeBridge;
    }
    if (fudge <= tunnel) {
        fudge = tunnel;
    }
    if (fudge <= cliff) {
        fudge = cliff;
    }
    if (fudge <= bridge) {
        fudge = bridge;
    }
    return TechnoClass::unknown_slot176() + fudge + adjust;
}
