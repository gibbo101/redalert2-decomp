// void TeamTypeClass::unknown_func_6c0180() (0x006C0180)
// Recomputes +0xE4 (the movement zones of the task force's types combined
// through 0x0056A900, starting at 9), +0xE8 (false once a naval type
// without passengers is found, or for base defense) and +0xE9 (a naval
// type carries passengers).
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/techno_type.hpp"
#include "shared/zone_table.hpp"

void TeamTypeClass::unknown_func_6c0180()
{
    unknown_e8 = true;
    unknown_e9 = false;
    unknown_e4 = 9;
    for (int index = 0; index < TaskForce->CountEntries; index++) {
        TechnoTypeClass *type = TaskForce->Entries[index].Type;
        if (type->Naval) {
            if (type->Passengers == 0) {
                unknown_e8 = false;
            } else {
                unknown_e9 = true;
            }
        }
        unknown_e4 = Unknown_0056A900(type->MovementZone, unknown_e4);
    }
    if (IsBaseDefense) {
        unknown_e8 = false;
    }
}
