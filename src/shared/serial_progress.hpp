#ifndef RA2_SHARED_SERIAL_PROGRESS_HPP
#define RA2_SHARED_SERIAL_PROGRESS_HPP
#include "shared/unknown_globals.hpp"
#include "shared/abstract.hpp"
#include "shared/rect.hpp"
// The progress screen (ProgressScreen, 0x00A769E8).
#include "shared/progress_screen.hpp"

// Actual RTTI class of the connection manager: vtable007A7414 slot1=005D0660.
// Only declarations: external object's full layout is not needed here.
class NullModemClass {
public:
    int Service();
    int Receive_Serial_Packet_005d0630(void *buffer, int *length);
};
extern NullModemClass serial_manager_00a40a28;
extern unsigned int serial_session_flags_00a3fac0;
extern int serial_local_player_00a3fb38;
#endif
