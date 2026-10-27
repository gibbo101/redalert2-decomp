// Aircraft damage response (00415E70,slot86): particle or explosion effect after destruction.
#include "shared/aircraft.hpp"
#include "shared/particle_system.hpp"
#include "shared/anim.hpp"
#include "shared/crt_memory.hpp"
#include "shared/id_source.hpp"
// @ref ?unknown_slot86@FootClass@@UAEHPAHHPAVWarheadTypeClass@@PAVTechnoClass@@_NH@Z=004c6000
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??0ParticleSystemClass@@QAE@PAVParticleSystemTypeClass@@ABUCoordStruct@@PAVAbstractClass@@PAVTechnoClass@@1@Z=0060aa70
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
int AircraftClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6)
{
    int result = FootClass::unknown_slot86(damage, distance, warhead, source, forced, arg6);
    switch (result) {
    case 4: {
        unknown_slot216(0);
        if (warhead == Rules->unknown_cac) {
            int count = abs(unknown_id_source_a3d290->Random()() % 3) + 7;
            for (int remaining = count; remaining > 0; --remaining) {
                ParticleSystemClass *system = new ParticleSystemClass(Rules->unknown_cf4, Center_Coord(), 0, this, unknown_geometry_l);
                system->unknown_e5 = true;
            }
        } else if (Type->Explosion.Count() > 0) {
            unsigned choice;
            TypeList<AnimTypeClass *> *explosions;
            AnimTypeClass *selected;
            // Preserve RNG, list-count and selected-value reads before the position call.
            new AnimClass((choice = (unsigned)unknown_id_source_a3d290->Random()(),
                           explosions = &Type->Explosion,
                           selected = (*explosions)[choice % explosions->Count()]),
                          unknown_slot40(), 0, 1, 0x600, 0);
        }
        // The unknown integer parameter carries the original source pointer.
        if (!unknown_slot224((int)source)) unknown_slot60();
        break;
    }
    case 5:
        return 5;
    }
    return result;
}
