// VeinholeMonsterClass::VeinholeMonsterClass(NoInitClass const &) (0x0070F820)
// The constructor Load rebuilds objects with: registers in Array and builds the
// vein node block, the heap and the per-cell table. Body 389 bytes (the
// inventory stops at 172 inside the first operator new call).
#include "shared/veinhole.hpp"
#include "shared/cd_timer.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ??_7VeinholeMonsterClass@@6BIPersistStream@@@=007ae7a0
// @ref ??_7VeinholeMonsterClass@@6BIRTTITypeInfo@@@=007ae784
// @ref ??_7VeinholeMonsterClass@@6BINoticeSink@@@=007ae77c
// @ref ??_7VeinholeMonsterClass@@6BINoticeSource@@@=007ae774
// @ref ?unknown_cells_428ac0@@YIHXZ=00428ac0
// @ref ?unknown_veinhole_buffer_ad07a0@@3PAEA=00ad07a0

VeinholeMonsterClass::VeinholeMonsterClass(NoInitClass const &noinit) : ObjectClass(noinit), unknown_bc(noinit), unknown_d4(noinit)
{
    Array.Add(this);
    unknown_a0 = new UnknownVeinNode[Rules_Vein_Node_Count()];
    unknown_9c = new UnknownVeinHeap(Rules_Vein_Node_Count());
    unknown_9c->Clear();
    if (unknown_veinhole_buffer_ad07a0 == 0) {
        unknown_veinhole_buffer_ad07a0 = new unsigned char[unknown_cells_428ac0()];
    }
    unknown_b0 = new unsigned char[unknown_cells_428ac0()];
}
