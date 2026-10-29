// Red Alert's Remove: takes a foot object out of the team: clears its tag when it is the team's, counts down the task force slot it filled (found by type when slot is -1), unlinks it from the member list, idles it unless arg3, and when no remaining member is initiated (+0x579) flags the first one.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/task_force.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?unknown_a40774@@3HA=00a40774
// @ref ?unknown_func_4f52f0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?Attach_Tag@ObjectClass@@QAE_NPAVTagClass@@@Z=005d4430

bool TeamClass::Unknown_006B8FB0(FootClass *member, int slot, bool arg3)
{
    member->unknown_5a2 = true;
    if (this != member->Team) {
        return true;
    }
    if (member->unknown_34 == Tag && member->House != 0 && !member->House->unknown_func_4f52f0()) {
        member->Attach_Tag(0);
    }
    if (slot == -1 && Class != 0 && Class->TaskForce != 0) {
        for (slot = 0; slot < Class->TaskForce->CountEntries; slot++) {
            if (Class->TaskForce->Entries[slot].Type == member->Class_Of()) {
                break;
            }
        }
    }
    if (Class != 0 && Class->TaskForce != 0 && (unsigned)slot < (unsigned)Class->TaskForce->CountEntries) {
        unknown_84[slot]--;
    }
    bool first = false;
    FootClass *previous = 0;
    FootClass *current = Member;
    bool found = false;
    while (current != 0 && (!found || !first)) {
        if (current == member) {
            if (previous != 0) {
                previous->unknown_4c8 = current->unknown_4c8;
            } else {
                Member = (FootClass *)current->unknown_4c8;
            }
            FootClass *next = (FootClass *)current->unknown_4c8;
            current->unknown_4c8 = 0;
            current->Team = 0;
            current->SuspendedMission = -1;
            current->unknown_498 = 0;
            current->unknown_22c = 0;
            current = next;
            unknown_48--;
            found = true;
            unknown_4c -= member->unknown_slot168();
            continue;
        }
        first = first || current->unknown_579;
        previous = current;
        current = (FootClass *)current->unknown_4c8;
    }
    if (member->Team != 0) {
        member->Team = 0;
    }
    if (unknown_a40774 == 0 && member->unknown_7d && !member->unknown_37d && !member->unknown_76 && !arg3) {
        member->unknown_slot261(false, true);
    }
    if (!first && Member != 0) {
        Member->unknown_579 = true;
        unknown_34 = 0;
    }
    JustDisappeared = true;
    NeedsToDisappear = true;
    return true;
}
