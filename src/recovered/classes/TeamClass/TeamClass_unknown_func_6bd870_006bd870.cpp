// Fills a list with the techno types the team type's task force still lacks: every entry's type once per count, minus one for each current member.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"

void TeamClass::unknown_func_6bd870(DynamicVectorClass<TechnoTypeClass *> &types)
{
    for (int index = 0; index < Class->TaskForce->CountEntries; index++) {
        TechnoTypeClass *type = Class->TaskForce->Entries[index].Type;
        for (int count = Class->TaskForce->Entries[index].Amount; count > 0; count--) {
            types.Add(type);
        }
    }
    for (FootClass *member = Member; member != 0; member = (FootClass *)member->unknown_4c8) {
        TechnoTypeClass *type = member->unknown_slot32();
        types.Delete(type);
    }
}
