// The member that should lead the team: the live one (on the map or an aircraft) with the highest LeadershipRating; the first member when none qualifies.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_a40774@@3HA=00a40774

// Red Alert's _Is_It_Playing: a member that is alive (0x006BDD80, Red Alert's _Is_It_Breathing) and
// in place or an aircraft. File-local inline of the Team unit; callers after this point may use it.
static inline bool _Is_It_Playing(FootClass *object)
{
    return TeamClass::unknown_func_6bdd80(object) && (object->unknown_579 || object->Kind_Of() == 2);
}

FootClass *TeamClass::unknown_func_6baa60()
{
    FootClass *member = Member;
    FootClass *leader = Member;
    int best = -1;
    for (; member != 0; member = (FootClass *)member->unknown_4c8) {
        int rating = member->unknown_slot32()->LeadershipRating;
        if (_Is_It_Playing(member) && rating > best) {
            leader = member;
            best = rating;
        }
    }
    return leader;
}
