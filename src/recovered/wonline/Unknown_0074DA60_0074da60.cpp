// WOL::User *Unknown_0074DA60() (0x0074DA60)
// The first user of the user list whose flags have bit 0 set (the game host), copied into
// unknown_user_b2a658; 0 when there is none.
#include "shared/wol_sink.hpp"
#include "shared/session_state.hpp"
// @ref ?unknown_users_b2a728@@3VWolUserArray@@A=00b2a728
// @ref ?unknown_user_b2a658@@3UUser@WOL@@A=00b2a658

WOL::User *Unknown_0074DA60()
{
    for (int i = 0; i < unknown_users_b2a728.Count; ++i) {
        unknown_users_b2a728.Get_Copy(unknown_user_b2a658, i);
        if (unknown_user_b2a658.flags & 1) return &unknown_user_b2a658;
    }
    return 0;
}
