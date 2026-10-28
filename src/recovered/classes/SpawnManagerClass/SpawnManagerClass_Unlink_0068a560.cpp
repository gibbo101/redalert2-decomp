// void SpawnManagerClass::Unlink(AbstractClass *object) (0x0068A560)
// Forgets a dying object: the destination (then the queued target takes
// over, if any), the queued target, one of its units (whose record then
// waits RegenRate frames, unless a healthy non-missile unit is only being
// detached) or the owner (every unit dies).
#include "shared/spawn_manager.hpp"
#include "shared/aircraft.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Abandon_Target@SpawnManagerClass@@QAEXXZ=0068a4b0
// @ref ?Kill_Nodes@SpawnManagerClass@@QAEXXZ=00689b70

void SpawnManagerClass::Unlink(AbstractClass *object)
{
    if (object == Destination) {
        Destination = 0;
        if (!Target) {
            Abandon_Target();
        }
        return;
    }
    if (object == Target) {
        Target = 0;
        return;
    }
    for (int i = SpawnedNodes.Count() - 1; i >= 0; i--) {
        if (object == SpawnedNodes[i]->Unit) {
            AircraftClass *unit = SpawnedNodes[i]->Unit;
            if (unit->Strength > 0 && !unit->unknown_5b2 && SpawnedNodes[i]->IsMissile != 1) {
                return;
            }
            SpawnedNodes[i]->Unit = 0;
            SpawnedNodes[i]->Status = 7;
            SpawnedNodes[i]->Timer = RegenRate;
            return;
        }
    }
    if (object == Owner) {
        Kill_Nodes();
        Abandon_Target();
    }
}
