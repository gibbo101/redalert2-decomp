// void SpawnManagerClass::Kill_Nodes() (0x00689B70)
// Every live record loses its unit: docked units are removed, launching ones
// leave the missile tracker first, and flying ones are handed to the tracker
// to finish at the destination. Each record then waits RegenRate frames.
#include "shared/spawn_manager.hpp"
#include "shared/aircraft.hpp"
#include "shared/kamikaze_tracker.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?KamikazeTracker@@3VKamikazeTrackerClass@@A=00a6e428
// @ref ?Add@KamikazeTrackerClass@@QAEXPAVAircraftClass@@PAVAbstractClass@@@Z=005316a0
// @ref ?Detach@KamikazeTrackerClass@@QAEXPAVAbstractClass@@@Z=00531880

void SpawnManagerClass::Kill_Nodes()
{
    for (int i = SpawnedNodes.Count() - 1; i >= 0; i--) {
        int status = SpawnedNodes[i]->Status;
        if (status == 7) {
            continue;
        }
        if (status == 0 || status == 6) {
            SpawnedNodes[i]->Status = 7;
            SpawnedNodes[i]->Unit->unknown_slot60();
            SpawnedNodes[i]->Unit = 0;
            SpawnedNodes[i]->Timer = RegenRate;
        } else if (status == 1) {
            KamikazeTracker.Detach(SpawnedNodes[i]->Unit);
            SpawnedNodes[i]->Status = 7;
            SpawnedNodes[i]->Unit->unknown_slot60();
            SpawnedNodes[i]->Unit = 0;
            SpawnedNodes[i]->Timer = RegenRate;
        } else {
            SpawnedNodes[i]->Status = 7;
            KamikazeTracker.Add(SpawnedNodes[i]->Unit, Destination);
            SpawnedNodes[i]->Unit = 0;
            SpawnedNodes[i]->Timer = RegenRate;
        }
    }
}
