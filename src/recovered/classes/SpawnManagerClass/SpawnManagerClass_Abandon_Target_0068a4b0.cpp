// void SpawnManagerClass::Abandon_Target() (0x0068A4B0)
// Flying missile spawns go to the missile tracker to finish at the
// destination and are unlinked; then the manager forgets its targets.
#include "shared/spawn_manager.hpp"
#include "shared/aircraft.hpp"
#include "shared/kamikaze_tracker.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?KamikazeTracker@@3VKamikazeTrackerClass@@A=00a6e428
// @ref ?Add@KamikazeTrackerClass@@QAEXPAVAircraftClass@@PAVAbstractClass@@@Z=005316a0
// @ref ?Unlink@SpawnManagerClass@@QAEXPAVAbstractClass@@@Z=0068a560

void SpawnManagerClass::Abandon_Target()
{
    for (int i = 0; i < SpawnedNodes.Count(); i++) {
        if (SpawnedNodes[i]->Status == 2 && SpawnedNodes[i]->Unit->Type->MissileSpawn) {
            KamikazeTracker.Add(SpawnedNodes[i]->Unit, Destination);
            KamikazeTracker.Timer = 2;
            Unlink(SpawnedNodes[i]->Unit);
        }
    }
    Status = 0;
    Target = 0;
    Destination = 0;
}
