// int SpawnManagerClass::Docked_Count() const (0x0068A650)
#include "shared/spawn_manager.hpp"

int SpawnManagerClass::Docked_Count() const
{
    int count = 0;
    for (int i = 0; i < SpawnedNodes.Count(); i++) {
        int status = SpawnedNodes[i]->Status;
        if (status == 6 || status == 0) {
            count++;
        }
    }
    return count;
}
