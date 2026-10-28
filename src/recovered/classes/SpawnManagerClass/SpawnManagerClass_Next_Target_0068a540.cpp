// bool SpawnManagerClass::Next_Target() (0x0068A540)
#include "shared/spawn_manager.hpp"

bool SpawnManagerClass::Next_Target()
{
    if (Target) {
        Destination = Target;
        Target = 0;
        return true;
    }
    return false;
}
