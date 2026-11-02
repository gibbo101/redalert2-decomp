// int unknown_session_kind() -- 0x0073A2E0
// Purpose: the session kind the online state at 0x00A3D2A4 needs: 0 when the
// state is 0 or 5 (no login), 2 for state 2 and 1 for any other state. Inline
// helper of Wonline_Main 0x0073A300 (same unit), also emitted out of line.
// Assumptions: the state's meaning is a hypothesis (shared/wol_main.hpp).
#include "shared/wol_main.hpp"
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4

int unknown_session_kind()
{
    if (unknown_a3d2a4 != 0 && unknown_a3d2a4 != 5) {
        return (unknown_a3d2a4 == 2) + 1;
    }
    return 0;
}
