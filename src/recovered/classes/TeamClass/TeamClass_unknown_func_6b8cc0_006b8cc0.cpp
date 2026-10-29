// Adds a foot object to the team (when it may join): leaves its old team, becomes the first member in the list, takes the team type's group and tag, and counts it.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/team_type.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_func_6b8dc0@TeamClass@@QAE_NPAVFootClass@@PAH@Z=006b8dc0
// @ref ?Unknown_006B8FB0@TeamClass@@QAE_NPAVFootClass@@H_N@Z=006b8fb0
// @ref ?Get_Group@TeamTypeClass@@QBEHXZ=006bfa60
// @ref ?Attach_Tag@ObjectClass@@QAE_NPAVTagClass@@@Z=005d4430
// @ref ?unknown_func_6b9610@TeamClass@@QAEXPAPAVAbstractClass@@0@Z=006b9610

bool TeamClass::unknown_func_6b8cc0(FootClass *member)
{
    if (member == 0) {
        return false;
    }
    int slot;
    if (!unknown_func_6b8dc0(member, &slot)) {
        return false;
    }
    if (member->Team != 0) {
        member->Team->Unknown_006B8FB0(member, -1, 0);
    }
    unknown_84[slot]++;
    member->unknown_579 = Member == 0;
    member->unknown_4c8 = Member;
    Member = member;
    member->Team = this;
    member->unknown_1ac = Class->Get_Group();
    if (Tag != 0) {
        if (!Class->OnTransOnly || member->unknown_slot32()->Passengers > 0) {
            member->Attach_Tag(Tag);
        }
    }
    unknown_48++;
    unknown_4c += member->unknown_slot168();
    if (unknown_34 == 0) {
        unknown_func_6b9610(&unknown_34, &unknown_38);
    }
    JustDisappeared = true;
    NeedsToDisappear = true;
    member->unknown_37a = Class->AreTeamMembersRecruitable;
    return true;
}
