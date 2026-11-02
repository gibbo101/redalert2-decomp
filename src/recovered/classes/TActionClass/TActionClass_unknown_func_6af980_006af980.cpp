// bool TActionClass::unknown_func_6af980(...) (0x006AF980)
// Calls slot 60 on every active particle system that stands on the cell of waypoint +0x44; always true.
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/particle_system.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?ParticleSystems@@3V?$DynamicVectorClass@PAVParticleSystemClass@@@@A=00a32280

bool TActionClass::unknown_func_6af980(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    for (int index = 0; index < ParticleSystems.Count(); index++) {
        ParticleSystemClass *system = ParticleSystems[index];
        if (system->unknown_7d && system->unknown_slot104() == waypoint) {
            system->unknown_slot60();
        }
    }
    return true;
}


