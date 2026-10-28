// int SpawnManagerClass::Launching_Count() const (0x0068A680)
#include "shared/spawn_manager.hpp"

int SpawnManagerClass::Launching_Count() const
{
    int count = 0;
    for (int i = 0; i < SpawnedNodes.Count(); i++) {
        if (SpawnedNodes[i]->Status == 1) {
            count++;
        }
    }
    return count;
}
