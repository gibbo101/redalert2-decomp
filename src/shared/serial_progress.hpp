#ifndef RA2_SHARED_SERIAL_PROGRESS_HPP
#define RA2_SHARED_SERIAL_PROGRESS_HPP
#include "shared/unknown_globals.hpp"
#include "shared/abstract.hpp"
#include "shared/rect.hpp"

// Actual RTTI class of the connection manager: vtable007A7414 slot1=005D0660.
// Only declarations: external object's full layout is not needed here.
class NullModemClass {
public:
    int Service();
    int Receive_Serial_Packet_005d0630(void *buffer, int *length);
};
// Actual global's non-RTTI vptr007A843C is written by0061ECC0.
// Only the observed method ABI is claimed, not its original class name/layout.
class UnknownProgressIndicator {
public:
    void Set_Progress_006201c0(int index, double value, Point2D point);
};
extern NullModemClass serial_manager_00a40a28;
extern UnknownProgressIndicator progress_indicator_00a769e8;
extern unsigned int serial_session_flags_00a3fac0;
extern int serial_local_player_00a3fb38;
#endif
