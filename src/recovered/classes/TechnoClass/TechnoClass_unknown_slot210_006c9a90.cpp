// void TechnoClass::unknown_slot210() (0x006C9A90, slot 210)
// Resets several states and the +0x238 object.
#include "shared/techno.hpp"
#include "shared/spawn_manager.hpp"
// @ref ?Kill_Nodes@SpawnManagerClass@@QAEXXZ=00689b70
// @ref ?Abandon_Target@SpawnManagerClass@@QAEXXZ=0068a4b0

void TechnoClass::unknown_slot210()
{
    unknown_slot220(0);
    unknown_slot260(0, 1);
    unknown_slot152(3);
    if (SpawnManager) {
        SpawnManager->Kill_Nodes();
        SpawnManager->Abandon_Target();
    }
    unknown_slot54(1);
    unknown_slot81();
}
