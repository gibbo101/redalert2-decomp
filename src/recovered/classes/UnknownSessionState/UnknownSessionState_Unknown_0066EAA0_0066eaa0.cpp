// SessionClass (the session object at 0x00A3D298, shared/unknown_globals.hpp UnknownSessionState).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/session_state.hpp"
#include "shared/vector_class.hpp"
#include "shared/string_table.hpp"
#include "shared/debug_printf.hpp"
#include "shared/house.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/abstract_type.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/ipx_conn.hpp"
#include "shared/connection.hpp"
#include "shared/owner_talk.hpp"
#include "shared/comm_buffer.hpp"
#include "shared/unknown_player_entry.hpp"
#include "shared/multi_mission.hpp"

// The call-waiting labels (0x007F3214: TXT_CWAIT_STAR70 and three more).
extern char const *unknown_call_wait_labels_7f3214[4];
// @ref ?unknown_call_wait_labels_7f3214@@3PAPBDA=007f3214
extern "C" unsigned short *__cdecl _wcsdup(unsigned short const *string);
// @ref __wcsdup=00797033
// @ref ??_C@_0BD@OFLC@D?3?2Ra2?2Session?4CPP?$AA@=007f33c8

void UnknownSessionState::Unknown_0066EAA0()
{
    for (int i = 0; i < 4; i++) {
        CallWaitStrings.Add(_wcsdup(StringTable::Load_String(unknown_call_wait_labels_7f3214[i], 0,
                                                            "D:\\Ra2\\Session.CPP", 536)));
    }
}
