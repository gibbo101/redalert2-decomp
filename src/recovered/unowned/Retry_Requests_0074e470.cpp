// Resends command 13 to each expired pending destination; operation name is a hypothesis.
#include "shared/session_state.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/wstring.hpp"
#include "shared/crt_memory.hpp"
#include "shared/debug_printf.hpp"

// @ref ?unknown_retry_format_7fefac@@3QBDB=0x007fefac
extern char const unknown_retry_format_7fefac[];
extern Wstring unknown_wstring_b26cb8;

void Retry_Requests_0074e470()
{
    for (int index = 0; index < unknown_session_a3d298.unknown_2f94; ++index) {
        if (unknown_session_a3d298.unknown_2f34[index] == 0) {
            UnknownGlobalPacket packet;
            memset(&packet, 0, sizeof(packet));
            packet.Command = 13;
            strcpy(packet.Name, unknown_wstring_b26cb8.Get());
            char const *name = Unknown_006FA120((unsigned short const *)unknown_player_slots_a3fa98[unknown_session_a3d298.unknown_2f14[index]]);
            Debug_Printf(unknown_retry_format_7fefac, name);
            unknown_ipx_manager_a40978.unknown_5259a0(&packet, 0x2f, 0,
                (wchar_t const *)unknown_player_slots_a3fa98[unknown_session_a3d298.unknown_2f14[index]]);
            unknown_session_a3d298.unknown_2f34[index] = CDTimerClass<SystemTimerClass>(1200);
        }
    }
}
