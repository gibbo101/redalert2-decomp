// void SpawnManagerClass::Set_Target(AbstractClass *target) (0x0068A490)
// Queues a new target; the current destination is not queued again.
#include "shared/spawn_manager.hpp"

void SpawnManagerClass::Set_Target(AbstractClass *target)
{
    if (target != Destination) {
        Target = target;
    }
}
