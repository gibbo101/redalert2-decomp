// void TechnoClass::unknown_6d96a0() (0x006D96A0)
// With more than 10 frames left on the +0x148 timer (and 0x00A40774
// clear), restarts it at 4-8 frames from the scenario's generator.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0

void TechnoClass::unknown_6d96a0()
{
    if (unknown_148.Value() > 10 && unknown_a40774 == 0) {
        unknown_148 = CDTimerClass<FrameTimerClass>(unknown_id_source_a3d290->Random()(4, 8));
    }
}
