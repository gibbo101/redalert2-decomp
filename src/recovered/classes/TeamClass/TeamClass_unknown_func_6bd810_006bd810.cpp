// Whether the team type's task force has a transporter entry (kind 3) that carries passengers.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"

bool TeamClass::unknown_func_6bd810()
{
    for (int index = 0; index < Class->TaskForce->CountEntries; index++) {
        TechnoTypeClass *type = Class->TaskForce->Entries[index].Type;
        if (type->Kind_Of() == 3 && type->Passengers > 0) {
            return true;
        }
    }
    return false;
}
