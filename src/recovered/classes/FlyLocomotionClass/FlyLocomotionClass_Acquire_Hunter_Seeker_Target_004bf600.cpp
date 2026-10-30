#include "shared/fly_locomotion.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/special.hpp"
#include "shared/id_source.hpp"
#include "shared/random.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??0?$VectorClass@PAVObjectClass@@@@QAE@IPBQAVObjectClass@@@Z=004bfbd0
// @ref ??_7?$DynamicVectorClass@PAVObjectClass@@@@6B@=0079db7c
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c

void __stdcall FlyLocomotionClass::Acquire_Hunter_Seeker_Target()
{
    if (LinkedTo->unknown_228 == 0) {
        DynamicVectorClass<ObjectClass *> aitargets;
        DynamicVectorClass<ObjectClass *> humantargets;

        bool atenemy = unknown_game_mode_a3d298 != 0 && LinkedTo->House->unknown_54f0 != -1 && !LinkedTo->House->unknown_func_4f52f0();

        for (int index = Technos.Count() - 1; index >= 0; index--) {
            TechnoClass *techno = Technos[index];

            bool enemy = true;
            if (!atenemy) {
                if (LinkedTo->House->Is_Ally(techno->House)) {
                    enemy = false;
                }
            } else {
                if (techno->House != Houses[LinkedTo->House->unknown_54f0]) {
                    enemy = false;
                }
            }

            if (enemy && techno->Strength > 0 && !techno->unknown_76 && techno->unknown_7d &&
                !techno->unknown_slot32()->Invisible && techno->unknown_slot32()->unknown_201 &&
                !(unknown_id_source_a3d290->Special().HarvesterImmune && techno->Kind_Of() == 1 && ((UnitClass *)techno)->Type->Harvester)) {

                if (unknown_game_mode_a3d298 != 0 && LinkedTo->House->unknown_func_4f52f0() && !techno->House->Type->MultiplayPassive &&
                    (techno->Kind_Of() == 1 || techno->Kind_Of() == 6 || techno->Kind_Of() == 15 || techno->Kind_Of() == 2)) {
                    humantargets.Add(techno);
                } else {
                    aitargets.Add(techno);
                }
            }
        }

        if (humantargets.Count() > 0) {
            LinkedTo->unknown_slot220(humantargets[unknown_id_source_a3d290->Random()(0, humantargets.Count() - 1)]);
        } else if (aitargets.Count() > 0) {
            LinkedTo->unknown_slot220(aitargets[unknown_id_source_a3d290->Random()(0, aitargets.Count() - 1)]);
        }
    }
}
