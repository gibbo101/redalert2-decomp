// void TeamTypeClass::Detach(AbstractClass *target, bool all) (0x006BF2D0)
// Forgets target as tag, owner, task force or script, then lets the script
// type forget it too.
#include "shared/team_type.hpp"
#include "shared/script.hpp"

void TeamTypeClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Tag == target) {
        Tag = 0;
    }
    if ((AbstractClass *)Owner == target) {
        Owner = 0;
    }
    if ((AbstractClass *)TaskForce == target) {
        TaskForce = 0;
    }
    if ((AbstractClass *)Script == target) {
        Script = 0;
    }
    if (Script != 0) {
        Script->Detach(target, all);
    }
}
