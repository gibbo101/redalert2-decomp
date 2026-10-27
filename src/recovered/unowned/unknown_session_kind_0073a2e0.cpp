// int unknown_session_kind() -- 0x0073A2E0
// Purpose: 0 when the online state at 0x00A3D2A4 is 0 or 5; otherwise 2
// for state 2 and 1 for any other state.
// Assumptions: the state's meaning is a hypothesis (shared/wol_sink.hpp).
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4

extern int unknown_a3d2a4;              // 0x00A3D2A4

int unknown_session_kind()
{
    if (unknown_a3d2a4 != 0 && unknown_a3d2a4 != 5) {
        return (unknown_a3d2a4 == 2) + 1;
    }
    return 0;
}
