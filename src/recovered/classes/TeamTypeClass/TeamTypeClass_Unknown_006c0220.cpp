// void Unknown_006c0220() (0x006C0220)
// Recomputes the task-force flags of every team type (TeamTypeClass 0x006C0180), after the scenario's team types are read.
#include "shared/team_type.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?TeamTypes@@3V?$DynamicVectorClass@PAVTeamTypeClass@@@@A=00a40c48

void __fastcall Unknown_006c0220()
{
    for (int index = 0; index < TeamTypes.Count(); index++) {
        TeamTypes[index]->unknown_func_6c0180();
    }
}
