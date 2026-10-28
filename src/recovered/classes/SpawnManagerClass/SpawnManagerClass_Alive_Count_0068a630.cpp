// int SpawnManagerClass::Alive_Count() const (0x0068A630)
#include "shared/spawn_manager.hpp"

int SpawnManagerClass::Alive_Count() const
{
    int count = 0;
    for (int i = 0; i < SpawnedNodes.Count(); i++) {
        if (SpawnedNodes[i]->Status != 7) {
            count++;
        }
    }
    return count;
}
