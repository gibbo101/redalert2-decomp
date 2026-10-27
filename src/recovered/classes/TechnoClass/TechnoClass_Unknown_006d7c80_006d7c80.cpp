// void __fastcall Unknown_006D7C80(AbstractClass *target) (0x006D7C80)
// Forgets an object that is going away: every techno that targets it drops
// the target (an aircraft on mission 0x19 also drops +0xA8 and +0x5BA), and
// every team clears its +0x3C and +0x40 references to it.
#include "shared/techno.hpp"
#include "shared/aircraft.hpp"
#include "shared/team.hpp"
// @ref ?Teams@@3V?$DynamicVectorClass@PAVTeamClass@@@@A=00866178

void __fastcall Unknown_006D7C80(AbstractClass *target)
{
    for (int index = Technos.Count() - 1; index >= 0; index--) {
        TechnoClass *techno = Technos[index];
        if (techno->unknown_228 == target) {
            techno->unknown_slot120();
            if (techno->Kind_Of() == 2 && techno->Mission == 0x19) {
                techno->unknown_a8 = 0;
                ((AircraftClass *)techno)->unknown_5ba = false;
            }
            if (techno->unknown_228 == target) {
                techno->unknown_slot220(0);
            }
        }
    }
    for (int team_index = Teams.Count() - 1; team_index >= 0; team_index--) {
        TeamClass *team = Teams[team_index];
        if (team->unknown_3c == target) {
            team->unknown_3c = 0;
        }
        if (team->unknown_40 == target) {
            team->unknown_40 = 0;
        }
    }
}
