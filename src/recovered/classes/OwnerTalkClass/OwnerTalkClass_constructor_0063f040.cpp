// OwnerTalkClass (shared/owner_talk.hpp): the packet-router talk unit at 0x0063ED70.
#define IPX_ADDRESS_DESTRUCTOR
#include "shared/vector_class.hpp"
#include "shared/owner_talk.hpp"
#include "shared/ipx_address.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/session_state.hpp"
#include "shared/house.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/event.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/crt_stdio.hpp"

// 0x0063F040
OwnerTalkClass::OwnerTalkClass() : unknown_18(false), RouterProcess(0)
{
}
