// The member that should lead the team: the live one (on the map or an aircraft) with the highest LeadershipRating; the first member when none qualifies.
#include "shared/unit.hpp"
#include "shared/foot.hpp"
#include "shared/team.hpp"
#include "shared/techno_type.hpp"
// @ref ?unknown_a40774@@3HA=00a40774

FootClass *TeamClass::unknown_func_6baa60()
{
    FootClass *member = Member;
    FootClass *leader = member;
    int best = -1;
    for (; member != 0; member = (FootClass *)member->unknown_4c8) {
        int rating = member->unknown_slot32()->LeadershipRating;
        if (unknown_func_6bdd80(member) && (member->unknown_579 || member->Kind_Of() == 2) && rating > best) {
            leader = member;
            best = rating;
        }
    }
    return leader;
}
